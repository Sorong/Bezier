#include "beziersurface.hpp"
#include "beziersurfacecalculator.hpp"

#define VERTEXPOINTSCALE 0.2f

BezierSurface::BezierSurface(QMatrix4x4& model, const QVector4D& pos): Model(model, pos), t_(0), s_(0), horizontal_size_(0), vertical_size_(0), casteljau_(false), derivate_(false) {
}

BezierSurface::~BezierSurface()
{
}

void BezierSurface::init(QVector4D *position) {
	if(programs_.isEmpty() || coordinates_.isEmpty()) {
		return;
	}
	createSubModels();
	Model::initBuffer();
	if(position) {
		this->setPosition(*position);
	}
	// Unbind vertex array object (
}

void BezierSurface::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	for(auto& program : programs_) {
		program->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}
	for(auto& ico : base_points_) {
		ico->setModelMatrix(this->model_);
		ico->translateToReference();
		ico->scale(VERTEXPOINTSCALE);
		ico->render(projection, view);
	}
	for(auto& curve : curves_) {
		curve->setModelMatrix(this->model_);
		curve->render(projection, view);
	}
	for(auto& strip : triangle_strips_) {
		strip->setModelMatrix(this->model_);
		strip->render(projection, view);
	}
	if(this->casteljau_) {
		for (auto& line : lines_) {
			line->setModelMatrix(this->model_);
			line->render(projection, view);
		}
	}
	if(this->derivate_line_) {
		derivate_line_->setModelMatrix(this->model_);
		derivate_line_->render(projection, view);
	}
}

void BezierSurface::reinit(QVector4D* pos) {

	for(int i = 0; i < base_points_.size(); i++) {
		vertices_[i] = base_points_[i]->getReference();
		base_points_[i]->reinit(pos);
	}
	QVector<QVector<QVector4D>> dest;
	BezierSurfaceCalculator calc;
	calc.bezierSurface(this->coordinates_, dest, 0.05, 0.05);
	for(int i = 0; i < this->curves_.size(); i++) {
		this->curves_[i]->setBaseCoordinates(dest[i]);
		curves_[i]->reinit(pos);
	}
	for(auto& strip : this->triangle_strips_) {
		strip->reinit(pos);
	}
	if(this->casteljau_) {
		createCasteljauLines();
		for (auto& line : lines_) {
			line->addShader(*this->programs_.at(0));
			line->init(pos);
		}
	}
	if(this->derivate_) {
		QVector4D derivate_src;
		QVector<QVector4D> derivate_vectors = calc.derivateSurface(this->coordinates_, this->t_, this->s_, &derivate_src);
		this->derivate_line_ = std::make_shared<Line>(model_, pos_);
		QVector<QVector4D> line;
		for(auto& vector : derivate_vectors) {
			line.push_back(derivate_src);
			line.push_back(derivate_src + vector);
		}
		derivate_line_->setCoordinates(line);
		derivate_line_->addShader(*this->programs_.at(0));
		derivate_line_->setColor({ 1,0,0,1 });
		derivate_line_->init(pos);
	}
	
	Model::reinit(pos);	
}

void BezierSurface::setT(float t) {
	this->t_ = t;
	if (this->casteljau_ || this->derivate_) {
		reinit();
	}
}

void BezierSurface::setS(float s) {
	this->s_ = s;
	if (this->casteljau_ ||this->derivate_) {
		reinit();
	}
}

void BezierSurface::addHorizontalCoordinates(QVector<QVector4D> &coordinates) {
	if(coordinates.size() != this->coordinates_.size()) {
		throw std::out_of_range("Invalid size, the surface cannot be increased");
	}
	for (auto i = 0; i < coordinates.size(); i++) {
		
		this->coordinates_[i].push_back(coordinates.at(i));
	}
}

void BezierSurface::addVerticalCoordinates(QVector<QVector4D> &coordinates) {
	if (coordinates.size() != this->coordinates_.at(0).size()) {
		throw std::out_of_range("Invalid size, the surface cannot be increased");
	}
	this->coordinates_.push_back(coordinates);
}


void BezierSurface::setCoordinates(QVector4DMatrix& coordinates) {
	recalculateSize();
	this->coordinates_ = coordinates;
}

QVector4DMatrix& BezierSurface::getCoordinates() {
	return this->coordinates_;
}

QVector4D& BezierSurface::get(int index) const {
	return this->base_points_.at(index)->getReference();
}

int BezierSurface::size() const {
	return this->base_points_.size();
}

QVector4D& BezierSurface::setClicked(int index) const {
	if(index < 0 || index >= this->base_points_.size()) {
		throw std::out_of_range("Index out of Bound");
	}
	this->base_points_.at(index)->setColor({ 1,0,0,1 });
	return this->base_points_.at(index)->getReference();
}

void BezierSurface::degreeElevation() {
	BezierSurfaceCalculator calculator;
	calculator.degreeElevationSurface(this->getCoordinates());
	clearAndReinit();
}

void BezierSurface::degreeElevationT() {
	BezierSurfaceCalculator calculator;
	calculator.degreeElevationTSurface(this->getCoordinates());
	clearAndReinit();
}

void BezierSurface::degreeElevationS() {
	BezierSurfaceCalculator calculator;
	calculator.degreeElevationSSurface(this->getCoordinates());
	clearAndReinit();
}

void BezierSurface::showCasteljau(bool state) {
	this->casteljau_ = state;
}

void BezierSurface::showDerivate(bool state) {
	this->derivate_ = state;
	if(!derivate_) {
		this->derivate_line_ = nullptr;
	}
}

void BezierSurface::createSubModels() {
	createBasePoints();
	QVector<QVector<QVector4D>> dest;
	BezierSurfaceCalculator calc;
	calc.bezierSurface(this->coordinates_, dest, 0.05, 0.05);
	createCurves(dest);
	for (auto& ico : base_points_) {
		ico->addShader(*this->programs_.at(0));
		//ico->setColor({ 1,1,1,1 });
		ico->init();
	}
	for (auto& curve : curves_) {
		curve->setColor({ 1,0,0,1 });
		curve->addShader(*this->programs_.at(0));
		curve->init();
	}
	for (auto& strip : triangle_strips_) {
		strip->addShader(*this->programs_.at(0));
		strip->init(nullptr);
	} 
}

void BezierSurface::clearSubModels() {
	this->base_points_.clear();
	this->vertices_.clear();
	this->curves_.clear();
	this->indices_.clear();
	this->triangle_strips_.clear();
	this->lines_.clear();
}

void BezierSurface::recalculateSize() {
	horizontal_size_ = 0;
	vertical_size_ = 0;
	if (!this->coordinates_.isEmpty()) {
		if (!this->coordinates_.at(0).isEmpty()) {
			horizontal_size_ = this->coordinates_.at(0).size();
			for (auto& horizontal : coordinates_) {
				if (horizontal_size_ != horizontal.size()) {
					throw std::out_of_range("Invalid size, the surface coordinates cannot be used");
				}
			}
		}
		vertical_size_ = this->coordinates_.size();
	}
}

void BezierSurface::createBasePoints() {
	auto horizonal_length = this->coordinates_.at(0).size();
	auto vertical_length = this->coordinates_.size();
	for (auto m = 0; m < vertical_length; m++) {
		auto n = 0;
		for (; n < horizonal_length; n++) {
			this->vertices_.push_back(this->coordinates_[m][n]);
			std::shared_ptr<Icosahedron> icosahedron = std::make_shared<Icosahedron>(model_, this->coordinates_[m][n]);
			icosahedron->setColor({ 1,1,1,1 });
			this->base_points_.push_back(icosahedron);
			if (n != horizonal_length - 1) {
				this->indices_.push_back((m * horizonal_length + n));
				this->indices_.push_back(m * horizonal_length + n + 1);
			}
			if (m != 0) {
				this->indices_.push_back(((m - 1) * horizonal_length + n));
				this->indices_.push_back((m * horizonal_length + n));
			}
		}
	}
	this->colors_.fill({ 0,1,0,1 }, this->vertices_.size());
}

void BezierSurface::createCurves(QVector4DMatrix& coordinates) {
	for (int i = 0; i < coordinates.size(); i++) {
		std::shared_ptr<BezierCurve> curve = std::make_shared<BezierCurve>(model_, pos_);
		curve->setBaseCoordinates(coordinates[i]);
		curves_.push_back(curve);
	}
	for (int i = 0; i < curves_.size() - 1; i++) {
		triangle_strips_.push_back(std::make_shared<TriangleStrip>(model_, curves_.at(i).get(), curves_.at(i + 1).get()));
	}
}

void BezierSurface::createCasteljauLines() {
	lines_.clear();
	QVector<QVector<QVector4D>> base;
	BezierSurfaceCalculator calc;
	calc.deCasteljauSurface(coordinates_, base, t_, s_);
	for(auto& coordinate : base) {
		std::shared_ptr<Line> line = std::make_shared<Line>(model_, pos_);
		line->setCoordinates(coordinate);
		line->setColor({ 1,1,1,1 });
		lines_.push_back(line);
	}
}

void BezierSurface::clearAndReinit(QVector4D* pos) {
	recalculateSize();
	clearSubModels();
	createSubModels();
	reinit();
}

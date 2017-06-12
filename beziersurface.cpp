#include "beziersurface.hpp"
#include "beziercalculator.hpp"

#define VERTEXPOINTSCALE 0.2f

BezierSurface::BezierSurface(QMatrix4x4& model, const QVector4D& pos): Model(model, pos), t_(0), s_(0) {
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
}

void BezierSurface::reinit(QVector4D* pos) {

	for(int i = 0; i < base_points_.size(); i++) {
		vertices_[i] = base_points_[i]->getReference();
		base_points_[i]->reinit(pos);
	}
	QVector<QVector<QVector4D>> dest;
	BezierCalculator calc;
	calc.calculateBezierSurface(this->coordinates_, dest, 0.05, 0.05);
	for(int i = 0; i < this->curves_.size(); i++) {
		this->curves_[i]->setBaseCoordinates(dest[i]);
		curves_[i]->reinit(pos);
	}
	for(auto& strip : this->triangle_strips_) {
		strip->reinit(pos);
	}
	Model::reinit(pos);	
}

void BezierSurface::setT(float t) {
	this->t_ = t;
}

void BezierSurface::setS(float s) {
	this->s_ = s;
}

void BezierSurface::addHorizontalCoordinates(QVector<QVector4D> &coordinates) {
	if(coordinates.size() != this->coordinates_.size()) {
		std::out_of_range("Invalid size, the surface cannot be increased");
	}
	for (auto i = 0; i < coordinates.size(); i++) {
		
		this->coordinates_[i].push_back(coordinates.at(i));
	}
}

void BezierSurface::addVerticalCoordinates(QVector<QVector4D> &coordinates) {
	if (coordinates.size() != this->coordinates_.at(0).size()) {
		std::out_of_range("Invalid size, the surface cannot be increased");
	}
	this->coordinates_.push_back(coordinates);
}


void BezierSurface::setCoordinates(QVector<QVector<QVector4D>> &coordinates) {
	this->coordinates_ = coordinates;
}

QVector<QVector<QVector4D>>& BezierSurface::getCoordinates() {
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
	BezierCalculator calculator;
	calculator.degreeElevationSurface(this->getCoordinates());
	this->base_points_.clear();
	this->vertices_.clear();
	this->curves_.clear();
	this->indices_.clear();
	this->triangle_strips_.clear();
	createSubModels();
	reinit();
}

void BezierSurface::createSubModels() {
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
	for (auto& vertex : vertices_) {
		vertex /= vertex.w();
	}
	QVector<QVector<QVector4D>> dest;
	BezierCalculator calc;
	calc.calculateBezierSurface(this->coordinates_, dest, 0.05, 0.05);
	for (int i = 0; i < dest.size(); i++) {
		std::shared_ptr<BezierCurve> curve = std::make_shared<BezierCurve>(model_, pos_);
		curve->setBaseCoordinates(dest[i]);
		curves_.push_back(curve);
	}
	for (int i = 0; i < dest.size() - 1; i++) {
		triangle_strips_.push_back(std::make_shared<TriangleStrip>(model_, curves_.at(i).get(), curves_.at(i + 1).get()));
	}
	this->colors_.fill({ 0,1,0,1 }, this->vertices_.size());

	for (auto& ico : base_points_) {
		ico->addShader(*this->programs_.at(0));
		//ico->setColor({ 1,1,1,1 });
		ico->init();
	}
	for (auto& curve : curves_) {
		curve->setColor({ 1,0,0, 1 });
		curve->addShader(*this->programs_.at(0));
		curve->init();
	}
	for (auto& strip : triangle_strips_) {
		strip->addShader(*this->programs_.at(0));
		strip->init(nullptr);
	}
}

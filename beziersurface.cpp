#include "beziersurface.hpp"
#include "beziersurfacecalculator.hpp"
#include "line.hpp"
#include "beziercurve.hpp"
#include "trianglestrip.hpp"
#include "icosahedron.hpp"

#define VERTEXPOINTSCALE 0.2f

BezierSurface::BezierSurface(QMatrix4x4& model, const QVector4D& pos) : Model(model, pos), surface_shader_(nullptr), u_(0), v_(0), horizontal_size_(0), vertical_size_(0), casteljau_(false), derivate_(false) {
}

BezierSurface::~BezierSurface()
{
}

void BezierSurface::init(QVector4D *position) {
	if (!default_shader_ || coordinates_.isEmpty()) {
		return;
	}
	createSubModels();
	Model::initBuffer();
	if (position) {
		this->setPosition(*position);
	}
	// Unbind vertex array object (
}

void BezierSurface::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	default_shader_->bind();
	default_shader_->setUniformValue("mvp", mvp);
	glBindVertexArray(this->vertexarrayobject_);
	glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(0);
	for (auto& ico : base_points_) {
		ico->setModelMatrix(this->model_);
		ico->translateToReference();
		ico->scale(VERTEXPOINTSCALE);
		ico->render(projection, view);
	}
	for (auto& curve : curves_) {
		curve->setModelMatrix(this->model_);
		curve->render(projection, view);
	}
	for (auto& strip : triangle_strips_) {
		strip->showNormals(this->show_normals_);
		strip->setModelMatrix(this->model_);
		strip->render(projection, view);
	}
	if (this->casteljau_) {
		for (auto& line : lines_) {
			line->setModelMatrix(this->model_);
			line->render(projection, view);
		}
	}
	if (this->derivate_line_) {
		derivate_line_->setModelMatrix(this->model_);
		derivate_line_->render(projection, view);
	}
}

void BezierSurface::reinit(QVector4D* pos) {

	for (int i = 0; i < base_points_.size(); i++) {
		vertices_[i] = base_points_[i]->getReference();
		base_points_[i]->reinit(pos);
	}
	QVector<QVector<QVector4D>> dest;
	QVector<QVector<QVector4D>> normals;
	BezierSurfaceCalculator calc;
	calc.bezierSurface(this->coordinates_, dest, 0.05, 0.05);
	calc.normalsSurface(this->coordinates_, normals, 0.05, 0.05);
	for (int i = 0; i < this->curves_.size(); i++) {
		this->curves_[i]->setBaseCoordinates(dest[i]);
		if (normals.size() >= coordinates_.size()) {
			curves_[i]->setNormals(normals[i]);
		}
		curves_[i]->reinit(pos);
	}
	for (auto& strip : this->triangle_strips_) {
		strip->reinit(pos);
	}
	if (this->casteljau_) {
		createCasteljauLines();
		for (auto& line : lines_) {
			line->setDefaultShader(*default_shader_);
			line->init(pos);
		}
	}
	if (this->derivate_) {
		QVector4D derivate_src;
		QVector<QVector4D> derivate_vectors = calc.derivateSurface(this->coordinates_, this->u_, this->v_, &derivate_src);
		this->derivate_line_ = std::make_shared<Line>(model_, pos_);
		QVector<QVector4D> line;
		for (auto& vector : derivate_vectors) {
			line.push_back(derivate_src);
			line.push_back(derivate_src + vector);
		}
		derivate_line_->setCoordinates(line);
		derivate_line_->setDefaultShader(*default_shader_);
		derivate_line_->setColor({ 1,0,0,1 });
		derivate_line_->init(pos);
	}

	Model::reinit(pos);
}

void BezierSurface::reinit(QVector4D* pos, bool hardreset) {
	if (hardreset) {
		clearAndReinit(pos);
	}
	else {
		reinit(pos);
	}
}

void BezierSurface::setU(float u) {
	this->u_ = u;
	if (this->casteljau_ || this->derivate_) {
		reinit();
	}
}

void BezierSurface::setV(float v) {
	this->v_ = v;
	if (this->casteljau_ || this->derivate_) {
		reinit();
	}
}

void BezierSurface::addHorizontalCoordinates(QVector<QVector4D> &coordinates) {
	if (coordinates_.isEmpty()) {
		addVerticalCoordinates(coordinates);
		return;
	}
	if (coordinates.size() != this->coordinates_.size()) {
		throw std::out_of_range("Invalid size, the surface cannot be increased");
	}
	for (auto i = 0; i < coordinates.size(); i++) {
		this->coordinates_[i].push_back(coordinates.at(i));
	}
	recalculateSize();
}

void BezierSurface::addVerticalCoordinates(QVector<QVector4D> &coordinates) {
	if (!coordinates_.isEmpty() && coordinates.size() != this->coordinates_.at(0).size()) {
		throw std::out_of_range("Invalid size, the surface cannot be increased");
	}
	this->coordinates_.push_back(coordinates);
	recalculateSize();
}


void BezierSurface::setCoordinates(QVector4DMatrix& coordinates) {
	this->coordinates_ = coordinates;
	recalculateSize();
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
	if (index < 0 || index >= this->base_points_.size()) {
		throw std::out_of_range("Index out of Bound");
	}
	this->base_points_.at(index)->setColor({ 1,0,0,1 });
	return this->base_points_.at(index)->getReference();
}

Clickable& BezierSurface::getClicked(int index) {
	return *this->base_points_[index];
}

Clickable& BezierSurface::getClicked(int index, int* row, int* col) {
	if (row && col) {
		*row = horizontal_size_ ? index / horizontal_size_ : 0;
		*col = vertical_size_ ? index % vertical_size_ : 0;
	}
	return getClicked(index);
}

void BezierSurface::degreeElevationUV() {
	BezierSurfaceCalculator calculator;
	calculator.degreeElevationSurface(this->getCoordinates());
	clearAndReinit();
}

void BezierSurface::degreeElevationU() {
	BezierSurfaceCalculator calculator;
	calculator.degreeElevationUSurface(this->getCoordinates());
	clearAndReinit();
}

void BezierSurface::degreeElevationV() {
	BezierSurfaceCalculator calculator;
	calculator.degreeElevationVSurface(this->getCoordinates());
	clearAndReinit();
}

void BezierSurface::showCasteljau(bool state) {
	this->casteljau_ = state;
}

void BezierSurface::showDerivate(bool state) {
	this->derivate_ = state;
	if (!derivate_) {
		this->derivate_line_ = nullptr;
	}
}

void BezierSurface::removeRow(int row) {
	if (row >= 0 || row < this->coordinates_.size()) {
		coordinates_.removeAt(row);
		recalculateSize();
	}
}

void BezierSurface::removeCol(int col) {
	if (!coordinates_.isEmpty() && (col >= 0 || col < this->coordinates_[0].size())) {
		for (int i = 0; i < coordinates_.size(); i++) {
			coordinates_[i].removeAt(col);
		}
		recalculateSize();
	}
}

void BezierSurface::removeRowAndCol(int row, int col) {
	removeRow(row);
	removeCol(col);
}

void BezierSurface::setSurfaceShader(QOpenGLShaderProgram& surface_shader) {
	this->surface_shader_ = &surface_shader;
}

void BezierSurface::setDefaultShader(QOpenGLShaderProgram& prog) {
	this->default_shader_ = &prog;
	if(!surface_shader_) {
		surface_shader_ = default_shader_;
	}
}

void BezierSurface::createSubModels() {
	createBasePoints();
	QVector4DMatrix dest;
	QVector4DMatrix normals;
	BezierSurfaceCalculator calc;
	calc.bezierSurface(this->coordinates_, dest, 0.05, 0.05);
	calc.normalsSurface(this->coordinates_, normals, 0.05, 0.05);
	createCurves(dest, normals);
	for (auto& ico : base_points_) {
		ico->setDefaultShader(*default_shader_);
		//ico->setColor({ 1,1,1,1 });
		ico->init();
	}
	for (auto& curve : curves_) {
		curve->setColor({ 1,0,0,1 });
		curve->setDefaultShader(*default_shader_);
		curve->addNormalShader(*this->normal_shader_);
		curve->init();
	}
	for (auto& strip : triangle_strips_) {
		strip->setDefaultShader(*surface_shader_);
		strip->addNormalShader(*this->normal_shader_);
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

void BezierSurface::createCurves(QVector4DMatrix& coordinates, QVector4DMatrix& normals) {
	for (int i = 0; i < coordinates.size(); i++) {
		std::shared_ptr<BezierCurve> curve = std::make_shared<BezierCurve>(model_, pos_);
		curve->setBaseCoordinates(coordinates[i]);
		if (normals.size() >= coordinates.size()) {
			curve->setNormals(normals[i]);
		}
		curves_.push_back(curve);
	}
	for (int i = 0; i < curves_.size() - 1; i++) {
		triangle_strips_.push_back(std::make_shared<TriangleStrip>(model_, curves_.at(i).get(), curves_.at(i + 1).get()));
	}
}

void BezierSurface::createCasteljauLines() {
	lines_.clear();
	QVector4DMatrix base;
	BezierSurfaceCalculator calc;
	calc.deCasteljauSurface(coordinates_, base, u_, v_);
	for (auto& coordinate : base) {
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

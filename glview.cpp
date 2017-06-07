#include <memory>
#include <QMatrix4x4>
#include <QDir>
#include <QPainter>
#include <QKeyEvent>
#include "glview.hpp"
#include "icosahedron.hpp"


#define SHADERPATH "/shader/"
#define ZNEAR 0.1f
#define ZFAR 100.0f
#define EYE 0.0f, 0.0f, 10.0f
#define CENTER 0.0f, 0.0f, 0.0f
#define UP 0.0f, 1.0f, 0.0f
#define INITPOS 0.0f, 0.0f, -10.0f, 1.0f

#define BLACK 0.0f, 0.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define CYAN 0.0f, 1.0f, 1.0f
#define GRAY 0.6f, 0.6f, 0.6f
#define GREEN 0.0f, 1.0f, 0.0f
#define MAGENTA 1.0f, 0.0f, 1.0f
#define RED 1.0f, 0.0f, 0.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define YELLOW 1.0f, 1.0f, 0.0f
#define GRAY40 0.4f, 0.4f, 0.4f
#define BLOODRED 0.4f, 0.0f, 0.0f
#define LIGHTGREEN 0.2f, 0.5f, 0.2f
#define LIME  0.2f, 0.7f, 0.2f
#define DARKGREEN 0.0f, 0.4f, 0.0f

BezierScreen::BezierScreen(QWidget* parent) :
	QOpenGLWidget(parent),
	show_sublines_(false),
	show_derivate_(false),
	highest_grade_reached_(false),
	z_near_(ZNEAR),
	z_far_(ZFAR),
	zoom_factor_(1.0f),
	t_(0.0),
	base_(nullptr),
	bezier_curve_(nullptr),
	derivate_(nullptr) {
	this->model_ = new QMatrix4x4;
	this->view_ = new QMatrix4x4;
	this->projection_ = new QMatrix4x4;
	this->prog_ = new QOpenGLShaderProgram;
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

BezierScreen::~BezierScreen() {
	makeCurrent();
	delete this->model_;
	delete this->view_;
	delete this->projection_;
	delete this->prog_;

}

void BezierScreen::initializeGL() {
	initializeOpenGLFunctions();
	if (!initShader()) {
		qDebug() << this->prog_->log();
	}
	initBaseline();
	glClearColor(GRAY, 0.0);
	this->view_->setToIdentity();
	QVector3D eye(EYE);
	this->view_->lookAt(eye, {CENTER}, {UP});
	surface = new BezierSurface(*this->model_, { INITPOS });
	QVector<QVector<QVector4D>> test2 = { {{-2,0,0,1}, {2,0,0,1}, {4,0,0,1}},{{ -2,2,1,1 },{ 2,2,1,1 } ,{ 4,2,1,1 } },{{ -2,3,2,1 },{ 2,3,2,1 },{ 4,3,2,1 } } };
	surface->setCoordinates(test2);
	surface->addShader(*this->prog_);
	surface->init();
}

void BezierScreen::paintGL() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_NEVER);
	if (lines_.isEmpty()) {
		initSublines();
		drawDerivate();
	}
	if(surface != nullptr) {
		surface->render(*this->projection_, *this->view_);
	}

	this->base_->renderLine();
	for (auto& l : lines_) {
		l->renderLine();
	}
	if (this->bezier_curve_ != nullptr) {
		this->bezier_curve_->renderLine();
	}

	if (show_derivate_ && derivate_ != nullptr) {
		derivate_->initLine();
		derivate_->renderLine();
	}
	update();
}

void BezierScreen::resizeGL(int w, int h) {
	h = h < 1 ? 1 : h;
	glViewport(0, 0, w, h);
	this->projection_->setToIdentity();
	this->projection_->perspective(45.0f * this->zoom_factor_, static_cast<float>(w) / h, this->z_near_, this->z_far_);
}


void BezierScreen::setT(float t) {
	this->t_ = t;
	this->lines_.clear();
}

void BezierScreen::removeCoordinateByIndex(int i) {
	initializeOpenGLFunctions();
	makeCurrent();
	coordinates_.removeAt(i);
	initBaseline();
	lines_.clear();
	update();
}


bool BezierScreen::addCoordinate(float x, float y) {
	return this->addCoordinate({x,y,0,1});
}

bool BezierScreen::addCoordinate(QVector4D xyzw) {
	initializeOpenGLFunctions();
	makeCurrent();
	this->coordinates_.push_back(xyzw);
	initBaseline();
	this->derivate_ = nullptr;
	lines_.clear();
	if (highest_grade_reached_) {
		this->coordinates_.pop_back();
	}
	return !highest_grade_reached_;
}

QVector4D BezierScreen::getCoordinateByIndex(int i) const {
	if (coordinates_.isEmpty() || i > coordinates_.size() - 1) {
		return {0, 0, 0, 0};
	}
	return coordinates_.at(i);
}


void BezierScreen::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Plus:
		this->zoom_factor_ /= 1.01;
		this->projection_->setToIdentity();
		this->projection_->perspective(45.0f * zoom_factor_, static_cast<float>(width()) / height(), z_near_, z_far_);
		break;
	case Qt::Key_Minus:
		zoom_factor_ = zoom_factor_ * 1.05 > 3.5 ? zoom_factor_ : zoom_factor_ * 1.05;
		this->projection_->setToIdentity();
		this->projection_->perspective(45.0f * zoom_factor_, static_cast<float>(width()) / height(), z_near_, z_far_);
		break;
	case Qt::Key_Left:
		this->view_->rotate(2 * zoom_factor_, 0.0, 2, 0);
		break;
	case Qt::Key_Right:
		this->view_->rotate(2 * zoom_factor_, 0.0, -2, 0);
		break;
	case Qt::Key_Up:
		this->view_->rotate(2 * zoom_factor_, 2.0, 0, 0);
		break;
	case Qt::Key_Down:
		this->view_->rotate(2 * zoom_factor_, -2.0, 0, 0);
		break;
	}
}

void BezierScreen::mousePressEvent(QMouseEvent* event) {
	dragged_vertex_ = nullptr;
	QVector2D pos(event->pos());
	QRect viewp(0, 0, width(), height());
	QMatrix4x4 click_model = *this->model_;
	click_model.setColumn(3, { INITPOS });
	auto begin = QVector3D(pos, -10.0f).unproject(*this->view_ * click_model, *this->projection_, viewp);
	auto end = QVector3D(pos.x(), height() - pos.y(), 1.0f).unproject(*this->view_ * click_model, *this->projection_, viewp);
	QVector3D direction = (end - begin).normalized();
	float radius = 0.2f;
	float radius2 = radius * radius;

	for (auto i = 0; i < this->surface->size(); i++) {
		QVector4D *coord = surface->get(i);
		QVector3D L = (coord->toVector3DAffine() - begin);
		float tca = QVector3D::dotProduct(L, direction);
		if (tca < 0) {
			continue;
		}
		float d2 = QVector3D::dotProduct(L, L) - tca * tca;
		if (d2 > radius2) {
			continue;
		}
		float thc = sqrt(radius2 - d2);
		auto t_drag = tca - thc;
		dragged_vertex_ = coord;
		intersect_to_center_ = coord->toVector3DAffine() - begin;
		surface->setClicked(i);
		qDebug() << "clicked:" << coord;
		qDebug() << intersect_to_center_;
		break;
	}
	//for (auto& coord : coordinates_) {
	//	QVector3D L = (coord.toVector3DAffine() - begin);
	//	float tca = QVector3D::dotProduct(L, direction);
	//	if (tca < 0) {
	//		continue;
	//	}
	//	float d2 = QVector3D::dotProduct(L, L) - tca * tca;
	//	if (d2 > radius2) {
	//		continue;
	//	}
	//	float thc = sqrt(radius2 - d2);
	//	auto t_drag = tca - thc;
	//	dragged_vertex_ = &coord;
	//	intersect_to_center_ = coord.toVector3DAffine() - begin;
	//	qDebug() << "clicked:" << coord;
	//	qDebug() << intersect_to_center_;
	//}
	initializeOpenGLFunctions();
	makeCurrent();
	update();
}

void BezierScreen::mouseMoveEvent(QMouseEvent* event) {
	if (dragged_vertex_ == nullptr) {
		return;
	}
	QVector2D pos(event->pos());
	QRect viewp(0, 0, width(), height());
	QMatrix4x4 click_model = *this->model_;
	click_model.setColumn(3, { INITPOS });
	auto begin = QVector3D(pos, -10.0f).unproject(*this->view_ * click_model, *this->projection_, viewp);
	auto end = QVector3D(pos.x(), height() - pos.y(), 1.0f).unproject(*this->view_ * click_model, *this->projection_, viewp);
	QVector3D direction = (end - begin).normalized();
	auto length = intersect_to_center_.length();
	float w = dragged_vertex_->w();
	*dragged_vertex_ = begin + length * direction;
	dragged_vertex_->setW(1);
	*dragged_vertex_ *= w;
	qDebug() << "new pos = " << *dragged_vertex_;
	makeCurrent();
	initBaseline();
	lines_.clear();
	surface->reinit();
}

void BezierScreen::mouseReleaseEvent(QMouseEvent* event) {

}

QVector<QVector4D> BezierScreen::getBasePoints() const {
	return this->base_->getVertices();
}


void BezierScreen::raiseElevation() {
	if (coordinates_.size() <= 2) {
		bezier_calculator_.degreeElevationSurface(surface->getCoordinates());
		surface->reinit();
		makeCurrent();
		update();

	}
	
/*	bezier_calculator_.degreeElevation(coordinates_);
	makeCurrent();
	initBaseline();
	lines_.clear();*/
}


void BezierScreen::toggleSublineMode(bool state) {
	this->show_sublines_ = state;
	lines_.clear();
	update();
}

void BezierScreen::toggleDerivateMode(bool state) {
	makeCurrent();
	this->show_derivate_ = state;
	update();
}


bool BezierScreen::initShader() const {
	QString path = QDir::currentPath() + SHADERPATH;
	QString vert = ".vert";
	QString frag = ".frag";
	if (!this->prog_->addShaderFromSourceFile(QOpenGLShader::Vertex, { path + "simple" + vert })) {
		return false;
	}
	if (!this->prog_->addShaderFromSourceFile(QOpenGLShader::Fragment, { path + "simple" + frag })) {
		return false;
	}
	return this->prog_->link();
}

void BezierScreen::initBaseline() {
	if (this->base_ != nullptr) {
		delete this->base_;
	}
	QVector<QVector4D> start_coordinates;
	for (auto& coordinate : this->coordinates_) {
		QVector4D current = coordinate;
		start_coordinates.push_back(current);
	}
	this->base_ = new Line(this->model_, this->view_, this->projection_, {BLUE}, start_coordinates);
	this->base_->setPosition({INITPOS});
	this->base_->setShader(this->prog_);
	this->base_->initLine();
	drawBezier();
}






void BezierScreen::initSublines() {
	drawDeCasteljau();
	if (lines_.isEmpty()) {
		return;
	}
	if (!show_sublines_) {

		lines_.at(lines_.size() - 1)->initLine();
	} else {
		for (auto& l : lines_) {
			l->initLine();
		}
	}
}

void BezierScreen::removeSublines() {
	this->lines_.clear();
}


void BezierScreen::drawDeCasteljau() {
	QVector3D col[] = {{RED},{GREEN},{MAGENTA}};
	int col_index = 0;
	QVector<QVector<QVector4D>> line_coordinates;
	bezier_calculator_.deCasteljau(this->coordinates_, line_coordinates, this->t_);
	//deCasteljau(base_coordinates, line_coordinates);
	for (auto& line_coord : line_coordinates) {
		std::shared_ptr<Line> curr(new Line(this->model_, this->view_, this->projection_, col[col_index++ % 3], line_coord));
		curr->setPosition({INITPOS});
		curr->setShader(this->prog_);
		this->lines_.push_back(std::shared_ptr<Line>(curr));
	}
}

void BezierScreen::drawBezier() {
	if (this->bezier_curve_ != nullptr) {
		delete this->bezier_curve_;
		this->bezier_curve_ = nullptr;
	}
	if (this->coordinates_.size() <= 2) {
		return;
	}
	QVector<QVector4D> points;
	highest_grade_reached_ = false;
	highest_grade_reached_ = !bezier_calculator_.calculateBeziercurve(this->coordinates_, points,0.05);
	if (highest_grade_reached_) {
		return;
	}

	this->bezier_curve_ = new Line(this->model_, this->view_, this->projection_, {BLACK}, points);
	this->bezier_curve_->setPosition({INITPOS});
	this->bezier_curve_->setShader(this->prog_);
	this->bezier_curve_->initLine();
}

void BezierScreen::drawDerivate() {
	if (this->derivate_ != nullptr) {
		delete this->derivate_;
		this->derivate_ = nullptr;
	}
	if (this->coordinates_.isEmpty() || this->lines_.isEmpty()) {
		return;
	}
	QVector4D start_point = this->lines_.last()->last();
	start_point /= start_point.w();
	auto last_point = bezier_calculator_.calculateDerivate(this->coordinates_, this->t_);
	last_point += start_point;
	this->derivate_ = new Line(this->model_, this->view_, this->projection_, {RED}, {start_point, last_point.normalized() * 2});
	this->derivate_->setPosition({INITPOS});
	this->derivate_->setShader(this->prog_);
}

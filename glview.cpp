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

GLView::GLView(QWidget* parent) :
	QOpenGLWidget(parent),
	show_sublines_(false),
	show_derivate_(false),
	highest_grade_reached_(false),
	z_near_(ZNEAR),
	z_far_(ZFAR),
	zoom_factor_(1.0f) {
	this->prog_ = new QOpenGLShaderProgram;
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

GLView::~GLView() {
	makeCurrent();
	delete this->prog_;

}

void GLView::initializeGL() {
	initializeOpenGLFunctions();
	if (!initShader()) {
		qDebug() << this->prog_->log();
	}
	glClearColor(GRAY, 0.0);
	this->view_.setToIdentity();
	QVector3D eye(EYE);
	this->view_.lookAt(eye, {CENTER}, {UP});

	//TODO: Removehardcoded Surface
	QMatrix4x4 model;
	surface = new BezierSurface(model, { INITPOS });
	QVector<QVector<QVector4D>> test2 = { {{-10,0,0,5}, {2,0,0,1}, {4,0,0,1}},{ { -2,2,0,1 },{ 2,2,0,1 },{ 4,2,0,1 } }/*,{ { -2,0,5,1 },{ 2,0,5,1 },{ 4,0,5,1 } }*/ };
	surface->setCoordinates(test2);
	surface->addShader(*this->prog_);
	surface->init();
}

void GLView::paintGL() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	if(surface != nullptr) {
		surface->render(projection_, view_);
	}
	update();
}

void GLView::resizeGL(int w, int h) {
	h = h < 1 ? 1 : h;
	glViewport(0, 0, w, h);
	projection_.setToIdentity();
	projection_.perspective(45.0f * this->zoom_factor_, static_cast<float>(w) / h, this->z_near_, this->z_far_);
}


void GLView::setT(float t) {
	if(surface != nullptr) {
		this->surface->setT(t);
	}
}

//Todo: Remove for surface
void GLView::removeCoordinateByIndex(int i) {
	initializeOpenGLFunctions();
	makeCurrent();
	update();
}

//Todo: Add for surface
bool GLView::addCoordinate(float x, float y) {
	return this->addCoordinate({x,y,0,1});
}

//Todo: Add for surface
bool GLView::addCoordinate(QVector4D xyzw) {
	initializeOpenGLFunctions();
	makeCurrent();
	if (highest_grade_reached_) {
	}
	return !highest_grade_reached_;
}
//Todo: GetCoordinateByIndex for surface
QVector4D GLView::getCoordinateByIndex(int i) const {
	return { 0,0,0,0 };
}

//TODO: Rework shortcuts and/or effect of shortcuts
void GLView::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Plus:
		zoom_factor_ /= 1.01;
		projection_.setToIdentity();
		projection_.perspective(45.0f * zoom_factor_, static_cast<float>(width()) / height(), z_near_, z_far_);
		break;
	case Qt::Key_Minus:
		zoom_factor_ = zoom_factor_ * 1.05 > 3.5 ? zoom_factor_ : zoom_factor_ * 1.05;
		projection_.setToIdentity();
		projection_.perspective(45.0f * zoom_factor_, static_cast<float>(width()) / height(), z_near_, z_far_);
		break;
	case Qt::Key_Left:
		view_.rotate(2 * zoom_factor_, 0.0, 2, 0);
		break;
	case Qt::Key_Right:
		view_.rotate(2 * zoom_factor_, 0.0, -2, 0);
		break;
	case Qt::Key_Up:
		view_.rotate(2 * zoom_factor_, 2.0, 0, 0);
		break;
	case Qt::Key_Down:
		view_.rotate(2 * zoom_factor_, -2.0, 0, 0);
		break;
	default: break;
	}
}

void GLView::mousePressEvent(QMouseEvent* event) {
	dragged_vertex_ = nullptr;
	QVector2D pos(event->pos());
	QRect viewp(0, 0, width(), height());
	QMatrix4x4 click_model;
	click_model.setColumn(3, { INITPOS });
	auto begin = QVector3D(pos, -10.0f).unproject(this->view_ * click_model, this->projection_, viewp);
	auto end = QVector3D(pos.x(), height() - pos.y(), 1.0f).unproject(this->view_ * click_model, this->projection_, viewp);
	QVector3D direction = (end - begin).normalized();
	float radius = 0.2f;
	float radius2 = radius * radius;

	for (auto i = 0; i < this->surface->size(); i++) {
		QVector4D &coord = surface->get(i);
		QVector3D L = (coord.toVector3DAffine() - begin);
		float tca = QVector3D::dotProduct(L, direction);
		if (tca < 0) {
			continue;
		}
		float d2 = QVector3D::dotProduct(L, L) - tca * tca;
		if (d2 > radius2) {
			continue;
		}
		//float thc = sqrt(radius2 - d2);
		//auto t_drag = tca - thc;
		dragged_vertex_ = &surface->setClicked(i);
		intersect_to_center_ = coord.toVector3DAffine() - begin;
		qDebug() << "clicked:" << coord;
		qDebug() << intersect_to_center_;
		emit clickedVertex(dragged_vertex_);
		break;
	}

	initializeOpenGLFunctions();
	makeCurrent();
	update();
}

void GLView::mouseMoveEvent(QMouseEvent* event) {
	if (dragged_vertex_ == nullptr) {
		return;
	}
	QVector2D pos(event->pos());
	QRect viewp(0, 0, width(), height());
	QMatrix4x4 click_model;
	click_model.setColumn(3, { INITPOS });
	auto begin = QVector3D(pos, -10.0f).unproject(this->view_ * click_model, this->projection_, viewp);
	auto end = QVector3D(pos.x(), height() - pos.y(), 1.0f).unproject(this->view_ * click_model, this->projection_, viewp);
	QVector3D direction = (end - begin).normalized();
	auto length = intersect_to_center_.length();
	float w = dragged_vertex_->w();
	*dragged_vertex_ = begin + length * direction;
	dragged_vertex_->setW(1);
	*dragged_vertex_ *= w;
	qDebug() << "new pos = " << *dragged_vertex_;
	makeCurrent();
	emit clickedVertex(dragged_vertex_);
	surface->reinit();
}

void GLView::mouseReleaseEvent(QMouseEvent* event) {

}

QVector<QVector4D> GLView::getBasePoints() const {
	return { {} };
}


void GLView::raiseElevation() {
		if(surface == nullptr) {
			return;
		}
		makeCurrent();
		update();
		surface->degreeElevation();
}

//Todo: Enable Casteljau for surface
void GLView::toggleSublineMode(bool state) {
	this->show_sublines_ = state;
	update();
}

//Todo: Enable Derivate for surface
void GLView::toggleDerivateMode(bool state) {
	makeCurrent();
	update();
}

void GLView::editClickedVertex() {
	makeCurrent();
	surface->reinit();
	update();
}

bool GLView::initShader() const {
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

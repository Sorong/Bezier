#include <memory>
#include <QMatrix4x4>
#include <QDir>
#include <QPainter>
#include <QKeyEvent>
#include "glview.hpp"


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
	this->controller_ = new GLViewController(this);
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

GLView::~GLView() {
	makeCurrent();
	delete this->prog_;
	delete this->controller_;
}

void GLView::initializeGL() {
	initializeOpenGLFunctions();
	if (!initShader()) {
		qDebug() << this->prog_->log();
	}
	glClearColor(GRAY, 0.0);
	this->view_.setToIdentity();
	QVector3D eye(EYE);
	this->view_.lookAt(eye, { CENTER }, { UP });

	//TODO: Removehardcoded Surface
	QMatrix4x4 model;
	surface_ = new BezierSurface(model, { INITPOS });
	QVector<QVector<QVector4D>> test2 = { {{-10,0,0,5}, {2,0,0,1}, {4,0,0,1}},{{-2,2,0,1},{2,2,0,1},{4,2,0,1}} }; /*{ { -2,2,0,1 },{ 2,2,0,1 },{ 4,2,0,1 }*/
	/*,{ { -2,0,5,1 },{ 2,0,5,1 },{ 4,0,5,1 } }*/
	surface_->setCoordinates(test2);
	surface_->addShader(*this->prog_);
	surface_->init();
}

void GLView::paintGL() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glPointSize(3);

	if (surface_ != nullptr) {
		surface_->render(projection_, view_);
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
	makeCurrent();
	if (surface_ != nullptr) {
		this->surface_->setT(t);
	}
	update();
}

void GLView::setS(float s) {
	makeCurrent();
	if (surface_ != nullptr) {
		this->surface_->setS(s);
	}
	update();
}

//Todo: Remove for surface_
void GLView::removeCoordinateByIndex(int i) {
	initializeOpenGLFunctions();
	makeCurrent();
	update();
}

//Todo: Add for surface_
bool GLView::addCoordinate(float x, float y) {
	return this->addCoordinate({ x,y,0,1 });
}

//Todo: Add for surface_
bool GLView::addCoordinate(QVector4D xyzw) {
	initializeOpenGLFunctions();
	makeCurrent();
	if (highest_grade_reached_) {
	}
	return !highest_grade_reached_;
}

//Todo: GetCoordinateByIndex for surface_
QVector4D GLView::getCoordinateByIndex(int i) const {
	return { 0,0,0,0 };
}

//TODO: Rework shortcuts and/or effect of shortcuts
void GLView::keyPressEvent(QKeyEvent* event) {
	if (surface_ == nullptr) {
		return;
	}
	switch (event->key()) {
	case Qt::Key_Plus:
		surface_->scale(1.10);
		click_model_.scale(1.10);
		break;
	case Qt::Key_Minus:
		surface_->scale(0.9);
		click_model_.scale(0.9);
		break;
	case Qt::Key_Left:
		surface_->rotate(1, 0, -1, 0);
		click_model_.rotate(1, 0, -1, 0);
		break;
	case Qt::Key_Right:
		surface_->rotate(1, 0, 1, 0);
		click_model_.rotate(1, 0, 1, 0);
		break;
	case Qt::Key_Up:
		surface_->rotate(1, -1, 0, 0);
		click_model_.rotate(1, -1, 0, 0);
		break;
	case Qt::Key_Down:
		surface_->rotate(1, 1, 0, 0);
		click_model_.rotate(1, 1, 0, 0);
		break;
	default: break;
	}
}

void GLView::mousePressEvent(QMouseEvent* event) {
	controller_->mousePressEvent(event);
	initializeOpenGLFunctions();
	makeCurrent();
	update();
}

void GLView::mouseMoveEvent(QMouseEvent* event) {
	controller_->mouseMoveEvent(event);
}

void GLView::mouseReleaseEvent(QMouseEvent* event) {

}

QVector<QVector4D> GLView::getBasePoints() const {
	return { {} };
}


void GLView::degreeElevation() {
	if (surface_ != nullptr) {
		controller_->clearClicked();
		makeCurrent();
		update();
		surface_->degreeElevation();
	}
}

void GLView::degreeElevationT() {
	if (surface_ != nullptr) {
		controller_->clearClicked();
		makeCurrent();
		update();
		surface_->degreeElevationT();
	}
}

void GLView::degreeElevationS() {
	if (surface_ != nullptr) {
		controller_->clearClicked();
		makeCurrent();
		update();
		surface_->degreeElevationS();
	}
}

void GLView::toggleSublineMode(bool state) {
	this->show_sublines_ = state;
	this->surface_->showCasteljau(state);
	makeCurrent();
	surface_->reinit();
	update();


}

void GLView::toggleDerivateMode(bool state) {
	this->show_derivate_ = state;
	this->surface_->showDerivate(state);
	makeCurrent();
	surface_->reinit();
	update();
}

void GLView::modeSelect() const {
	this->controller_->setMode(SELECT);
}

void GLView::modeDrawCurve() const {
	this->controller_->setMode(DRAWCURVE);
}

void GLView::modeDrawSurface() const {
	this->controller_->setMode(DRAWSURFACE);
}

void GLView::modeDrawCoonspatch() const {
	this->controller_->setMode(DRAWCOONS);
}


void GLView::editClickedVertex() {
	makeCurrent();
	surface_->reinit();
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

#include <memory>
#include <QMatrix4x4>
#include <QDir>
#include <QPainter>
#include <QKeyEvent>
#include "glview.hpp"


#define SHADERPATH "/shader/"
#define ZNEAR 0.1f
#define ZFAR 100.0f
#define EYEZ 10.0f
#define EYE 0.0f, 0.0f, EYEZ
#define CENTER 0.0f, 0.0f, 0.0f
#define UP 0.0f, 1.0f, 0.0f
#define INITPOS -EYE, 1.0f
#define INITLIGHT 0.0f, 0.0f, EYEZ, 0.0f

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
	zoom_factor_(1.0f), eye(EYE) {
	this->light.pos = { INITLIGHT };
	this->light.ambient = { WHITE,1.0f };
	this->light.diffuse = { GRAY, 1.0f };
	this->light.specular = { WHITE, 1.0f };
	this->prog_ = new QOpenGLShaderProgram;
	this->normal_prog_ = new QOpenGLShaderProgram;
	this->phong_prog_ = new QOpenGLShaderProgram;
	//this->tess_prog_ = new QOpenGLShaderProgram;
	this->tess_prog_ = nullptr;
	this->controller_ = new GLViewController(this);
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

GLView::~GLView() {
	makeCurrent();
	delete this->prog_;
	delete this->normal_prog_;
	if(phong_prog_) {
		delete this->phong_prog_;
	}
	delete this->tess_prog_;
	delete this->controller_;
}

void GLView::initializeGL() {
	initializeOpenGLFunctions();
	if (!initShader()) {
		qDebug() << this->prog_->log();
	}
	if (!initNormalShader()) {
		qDebug() << this->normal_prog_->log();
	}
	if(phong_prog_ && !initPhongShader()) {
		qDebug() << this->phong_prog_->log();
	}
	if(tess_prog_ && !initTessShader()) {
		qDebug() << this->tess_prog_->log();
	}
	glClearColor(GRAY, 0.0);
	this->view_.setToIdentity();
	this->view_.lookAt(eye, { CENTER }, { UP });
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

	if (temp_model_) {
		temp_model_->render(projection_, view_);
	}
	for (auto& surface : surfaces_) {
		surface->render(projection_, view_);
	}
	for(auto& patch : patches_) {
		patch->render(projection_, view_);
	}
	update();
}

void GLView::resizeGL(int w, int h) {
	h = h < 1 ? 1 : h;
	glViewport(0, 0, w, h);
	projection_.setToIdentity();
	projection_.perspective(45.0f * this->zoom_factor_, static_cast<float>(w) / h, this->z_near_, this->z_far_);
}


void GLView::setU(float u) {
	makeCurrent();
	if (controller_->getSelectedSurface() != nullptr) {
		controller_->getSelectedSurface()->setU(u);
	}
	update();
}

void GLView::setV(float v) {
	makeCurrent();
	if (controller_->getSelectedSurface() != nullptr) {
		controller_->getSelectedSurface()->setV(v);
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


void GLView::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Plus:
		if (eye.z() != 0) {
			eye -= {0.0f, 0.0f, 1};
		}
		this->view_.setToIdentity();
		this->view_.lookAt(eye, { CENTER }, { UP });
		break;
	case Qt::Key_Minus:
		eye += {0.0f, 0.0f, 1};
		this->view_.setToIdentity();
		this->view_.lookAt(eye, { CENTER }, { UP });
		break;
		default: 
		break;
	}
	Model* selected_model;
	if (! ((selected_model = controller_->getSelectedSurface()))) {
		if(! ((selected_model = controller_->getSelectedCoonsPatch()))) {
			return;
		}
	}
	switch (event->key()) {
	case Qt::Key_Left:
	case Qt::Key_A:
		selected_model->rotate(1, 0, -1, 0);
		break;
	case Qt::Key_Right:
	case Qt::Key_D:
		selected_model->rotate(1, 0, 1, 0);
		break;
	case Qt::Key_Up:
	case Qt::Key_W:
		selected_model->rotate(1, -1, 0, 0);
		break;
	case Qt::Key_Down:
	case Qt::Key_S:
		selected_model->rotate(1, 1, 0, 0);
		break;
	case Qt::Key_Q:
		selected_model->rotate(1, 0, 0, -1);
		break;
	case Qt::Key_E:
		selected_model->rotate(1, 0, 0, 1);
		break;
	default:
		break;
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
	controller_->mouseReleaseEvent(event);
}

QVector<QVector4D> GLView::getBasePoints() const {
	return { {} };
}


void GLView::degreeElevation() {
	BezierSurface * ptr = controller_->getSelectedSurface();
	if (ptr != nullptr) {
		controller_->clearClicked();
		makeCurrent();
		update();
		ptr->degreeElevationUV();	
	}
}

void GLView::degreeElevationU() {
	BezierSurface * ptr = controller_->getSelectedSurface();
	if (ptr != nullptr) {
		controller_->clearClicked();
		makeCurrent();
		update();
		ptr->degreeElevationU();
	}
}

void GLView::degreeElevationV() {
	BezierSurface * ptr = controller_->getSelectedSurface();
	if (ptr != nullptr) {
		controller_->clearClicked();
		makeCurrent();
		update();
		ptr->degreeElevationV();
	}
}

void GLView::toggleSublineMode(bool state) {
	if (!controller_->getSelectedSurface()) {
		return;
	}
	this->show_sublines_ = state;
	controller_->getSelectedSurface()->showCasteljau(state);
	reinitCurrentSurface();
}

void GLView::toggleDerivateMode(bool state) {
	if (!controller_->getSelectedSurface()) {
		return;
	}
	this->show_derivate_ = state;
	controller_->getSelectedSurface()->showDerivate(state);
	reinitCurrentSurface();
}

void GLView::toggleNormals(bool show) {
	if (controller_->getSelectedSurface() != nullptr) {
		makeCurrent();
		update();
		controller_->getSelectedSurface()->showNormals(show);
	}
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

void GLView::modeC0() const {
	this->controller_->setMode(C0);
}

void GLView::setClampedZ(double z) const {
	this->controller_->setClampedZ(z);
}


void GLView::editClickedVertex() {
	reinitCurrentSurface();
}

void GLView::deleteSelected() {
	Model* selected_model;
	if (!((selected_model = controller_->getSelectedSurface()))) {
		if (!((selected_model = controller_->getSelectedCoonsPatch()))) {
			return;
		}
	}
	controller_->clearClicked();
	for(int i = 0; i < surfaces_.size(); i++) {
		if(selected_model == & *(surfaces_[i])) {
			surfaces_.remove(i);
		}
	}
	for(int j = 0; j < patches_.size(); j++) {
		if (selected_model == &*(patches_[j])) {
			patches_.remove(j);
		}
	}
}

void GLView::initModel(Model& model, QVector4D* pos) {
	makeCurrent();
	model.setDefaultShader(*this->prog_);
	model.init(pos);
	update();
}

void GLView::reinitCurrentSurface() {
	Model* selected_model;
	if (!((selected_model = controller_->getSelectedSurface()))) {
		if (!((selected_model = controller_->getSelectedCoonsPatch()))) {
			return;
		}
	}
	makeCurrent();
	selected_model->reinit();
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

bool GLView::initNormalShader() const {
	QString path = QDir::currentPath() + SHADERPATH;
	QString vert = ".vert";
	QString geom = ".geom";
	QString frag = ".frag";
	if (!this->normal_prog_->addShaderFromSourceFile(QOpenGLShader::Vertex, { path + "normal" + vert })) {
		return false;
	}
	if (!this->normal_prog_->addShaderFromSourceFile(QOpenGLShader::Geometry, { path + "normal" + geom })) {
		return false;
	}
	if (!this->normal_prog_->addShaderFromSourceFile(QOpenGLShader::Fragment, { path + "normal" + frag })) {
		return false;
	}
	return this->normal_prog_->link();
}

bool GLView::initPhongShader() const {
	if(!phong_prog_) {
		return false;
	}
	QString path = QDir::currentPath() + SHADERPATH;
	QString vert = ".vert";
	QString frag = ".frag";
	if (!this->phong_prog_->addShaderFromSourceFile(QOpenGLShader::Vertex, { path + "phong" + vert })) {
		return false;
	}
	if (!this->phong_prog_->addShaderFromSourceFile(QOpenGLShader::Fragment, { path + "phong" + frag })) {
		return false;
	}
	return this->phong_prog_->link();
}

bool GLView::initTessShader() const {

	if (!tess_prog_) {
		return false;
	}
	QString path = QDir::currentPath() + SHADERPATH;
	QString vert = ".vert";
	QString geom = ".geom";
	QString tes = ".tes";
	QString tcs = ".tcs";
	QString frag = ".frag";
	if (!this->tess_prog_->addShaderFromSourceFile(QOpenGLShader::Vertex, { path + "click" + vert })) {
		return false;
	}
	if (!this->tess_prog_->addShaderFromSourceFile(QOpenGLShader::TessellationControl, { path + "click" + tcs })) {
		return false;
	}
	if (!this->tess_prog_->addShaderFromSourceFile(QOpenGLShader::TessellationEvaluation, { path + "click" + tes })) {
		return false;
	}
	if (!this->tess_prog_->addShaderFromSourceFile(QOpenGLShader::Geometry, { path + "click" + geom })) {
		return false;
	}
	if (!this->tess_prog_->addShaderFromSourceFile(QOpenGLShader::Fragment, { path + "click" + frag })) {
		return false;
	}

	return true;
}



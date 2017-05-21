#include <memory>
#include <QMatrix4x4>
#include <QDir>
#include <QPainter>
#include <QKeyEvent>
#include "bezierscreen.h"

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
#define GRAY 0.4f, 0.4f, 0.4f
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
	ray = nullptr;
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

}

void BezierScreen::paintGL() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(2);
	glPointSize(7);
	if (ray != nullptr) {
		ray->renderLine();
	}
	if (coords_.isEmpty()) {
		QPainter painter(this);
		painter.setPen(Qt::darkRed);
		painter.setFont(QFont("Arial", 20));
		painter.drawText(0, 0, width(), height(), Qt::AlignCenter, "Keine Punkte vorhanden!");
		painter.end();
		update();
		return;
	}
	if (lines_.isEmpty()) {
		initSublines();
		drawDerivate();
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

void BezierScreen::raiseElevation() {
	if(coords_.size() <= 2) {
		return;
	}
	QVector<QVector4D> new_coords;
	new_coords.push_back(coords_.at(0));
	for (int i = 1, n = coords_.size()-1; i < coords_.size(); i++) {
		QVector4D new_b = static_cast<float>(i) / (n + 1) * coords_.at(i - 1) + (1 - static_cast<float>(i) / (n + 1)) * coords_.at(i);
		//new_b /= new_b.w();
		new_coords.push_back(new_b);
	}
	new_coords.push_back(coords_.at(coords_.size() - 1));
	this->coords_ = new_coords;
	makeCurrent();
	initBaseline();
	lines_.clear();
}

void BezierScreen::initBaseline() {
	if (this->base_ != nullptr) {
		delete this->base_;
	}
	QVector<QVector4D> start_coordinates;
	for (auto& coordinate : this->coords_) {
		QVector4D current = coordinate;
		start_coordinates.push_back(current);
	}
	this->base_ = new Line(this->model_, this->view_, this->projection_, {BLUE}, start_coordinates);
	this->base_->setPosition({INITPOS});
	this->base_->setShader(this->prog_);
	this->base_->initLine();
	drawBezier();
}

bool BezierScreen::addCoordinate(float x, float y) {
	return this->addCoordinate({x,y,0,1});
}

bool BezierScreen::addCoordinate(QVector4D xyzw) {
	initializeOpenGLFunctions();
	makeCurrent();
	this->coords_.push_back(xyzw);
	initBaseline();
	this->derivate_ = nullptr;
	lines_.clear();
	if(highest_grade_reached_) {
		this->coords_.pop_back();
	}
	return !highest_grade_reached_;
}


void BezierScreen::removeCoordinateByIndex(int i) {
	initializeOpenGLFunctions();
	makeCurrent();
	coords_.removeAt(i);
	initBaseline();
	lines_.clear();
	update();
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
	auto begin = QVector3D(pos, -10.0f).unproject(*this->view_* click_model, *this->projection_, viewp);
	auto end = QVector3D(pos.x(), height() - pos.y(), 1.0f).unproject(*this->view_* click_model, *this->projection_, viewp);
	QVector3D direction = (end - begin).normalized();


	QVector4D *closest = nullptr;
	float distance = std::numeric_limits<float>::max();

	float radius = 2.0f;
	float radius2 = radius * radius;
	for (auto& coord : coords_) {
		QVector3D L = (coord.toVector3D() - begin);
		float tca = QVector3D::dotProduct(L, direction);
		if (tca < 0) {
			continue;
		}
		float d2 = QVector3D::dotProduct(L, L) - tca * tca;
		if (d2 > radius2) {
			continue;
		}
		float thc = sqrt(radius2 - d2);
		t_drag_ = tca - thc;
		dragged_vertex_ = &coord;
		intersect_to_center_ = coord.toVector3D() - begin;
	}
	if (ray != nullptr) {
		delete ray;
	}
	
	initializeOpenGLFunctions();
	makeCurrent();
	ray = new Line(this->model_, this->view_, this->projection_, { RED }, { begin, end });
	ray->setPosition({ INITPOS });
	ray->setShader(this->prog_);
	ray->initLine();
	update();
}

void BezierScreen::mouseMoveEvent(QMouseEvent* event) {
	QVector2D pos(event->pos());
	QRect viewp(0, 0, width(), height());
	QMatrix4x4 click_model = *this->model_;
	click_model.setColumn(3, { INITPOS });
	auto begin = QVector3D(pos, -10.0f).unproject(*this->view_* click_model, *this->projection_, viewp);
	auto end = QVector3D(pos.x(), height() - pos.y(), 1.0f).unproject(*this->view_* click_model, *this->projection_, viewp);
	QVector3D direction = (end - begin).normalized();
	auto length = intersect_to_center_.length();
	float w = dragged_vertex_->w();
	*dragged_vertex_ = begin + length*direction;
	dragged_vertex_->setW(w);
	qDebug() << "new pos = " << *dragged_vertex_;
	makeCurrent();
	initBaseline();
	lines_.clear();
}

void BezierScreen::mouseReleaseEvent(QMouseEvent* event) {

}

QVector<QVector4D> BezierScreen::getBasePoints() const {
	return this->base_->getVertices();
}

void BezierScreen::toggleSublineMode(bool state) {
	this->show_sublines_ = state;
	lines_.clear();
}

void BezierScreen::toggleDerivateMode(bool state) {
	makeCurrent();
	this->show_derivate_ = state;
	update();
}

QVector4D BezierScreen::getCoordinateByIndex(int i) const {
	if (coords_.isEmpty() || i > coords_.size() - 1) {
		return {0, 0, 0, 0};
	}
	return coords_.at(i);
}

void BezierScreen::initSublines() {
	calcBezier();
	if(lines_.isEmpty()) {
		return;
	}
	if(!show_sublines_) {
		
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

bool BezierScreen::initShader() const {
	QString path = QDir::currentPath() + SHADERPATH;
	QString vert = ".vert";
	QString frag = ".frag";
	if (!this->prog_->addShaderFromSourceFile(QOpenGLShader::Vertex, {path + "simple" + vert})) {
		return false;
	}
	if (!this->prog_->addShaderFromSourceFile(QOpenGLShader::Fragment, {path + "simple" + frag})) {
		return false;
	}
	return this->prog_->link();
}

void BezierScreen::calcBezier() {
	QVector3D col[] = {{RED},{GREEN},{MAGENTA}};
	int col_index = 0;
	QVector<QVector4D> base_coords = this->coords_;
	QVector<QVector<QVector4D>> line_coords;
	deCasteljau(base_coords, line_coords);
	for(auto& line_coord : line_coords) {
		std::shared_ptr<Line> curr(new Line(this->model_, this->view_, this->projection_, col[col_index++ % 3], line_coord));
		curr->setPosition({ INITPOS });
		curr->setShader(this->prog_);
		this->lines_.push_back(std::shared_ptr<Line>(curr));
	}
}

void BezierScreen::drawBezier() {
	if (this->bezier_curve_ != nullptr) {
		delete this->bezier_curve_;
		this->bezier_curve_ = nullptr;
	}
	if(this->coords_.size() <= 2) {
		return;
	}
	QVector<QVector4D> points;
	highest_grade_reached_ = false;
	int n = this->coords_.length() - 1;
	if (n <= 0) {
		return;
	}
	for (int tAsInt = 0; tAsInt <= 100; tAsInt += 5) {
		float t = tAsInt/100.f;
		QVector<float> bernsteinpolynoms;
		float beziertest = 0;
		for (int k = 0; k <= n; k++) {
			auto polynom = binominal(n, k) * pow(t, k) * pow(1 - t, n - k);
			beziertest += polynom;
			bernsteinpolynoms.push_back(polynom);
			
		}
		if (beziertest*100 <= 99) {
			this->highest_grade_reached_ = true;
			return;
		}
		QVector4D point(0, 0, 0, 0);
		for (auto j = 0; j <= n; j++) {
			auto current = this->coords_.at(j);
			point += current*bernsteinpolynoms.at(j);
		}
		point /= point.w();
		points.push_back(point);
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
	if (this->coords_.isEmpty() || this->lines_.isEmpty()) { return; }
	QVector<QVector4D> points;
	QVector<float> bernsteinpolynoms;

	auto n = coords_.size()-1;
	for (auto j = 0; j < n; j++) {
		auto polynom = binominal((n-1), j) * pow(t_, j) * pow(1 - t_, (n-1) - j);
		bernsteinpolynoms.push_back(polynom);
	}

	QVector4D point(0, 0, 0, 0);
	for (auto j = 0; j < coords_.size() - 1; j++) {
		auto b1 = this->coords_.at(j + 1);
		auto b2 = this->coords_.at(j);
		auto current = (b1/b1.w()) - (b2/b2.w());
		point = current * bernsteinpolynoms.at(j);
		points.push_back(point);
	}
	QVector<QVector<QVector4D>> vector;
	//deCasteljau(points, vector);
	/*if(vector.isEmpty()) {
		return;
	}*/
	QVector4D start_point = this->lines_.last()->last();
	QVector4D last_point(0, 0, 0, 0);
	for(auto& curpoint : points) {
		last_point += curpoint;
	}
	//last_point.normalize();
	//last_point *= 2;
	start_point /= start_point.w();
	last_point += start_point;
	this->derivate_ = new Line(this->model_, this->view_, this->projection_, { RED }, { start_point, last_point });
	this->derivate_->setPosition({ INITPOS });
	this->derivate_->setShader(this->prog_);
}

void BezierScreen::deCasteljau(QVector<QVector4D> &base_coords, QVector<QVector<QVector4D>> &line_coords) const {
	QVector<QVector4D> new_line_points;

	for (int i = 0; i < base_coords.size() - 1; i++) {
		auto first_w = base_coords.at(i);
		auto second_w = base_coords.at(i + 1);
		auto b_i = (1 - this->t_) * base_coords.at(i) + t_ * base_coords.at(i + 1);
		new_line_points.push_back(b_i);
	}
	if (new_line_points.isEmpty()) {
		return;
	}
	line_coords.push_back(new_line_points);
	if (new_line_points.size() > 1) {
		deCasteljau(new_line_points, line_coords);
	}
}

int BezierScreen::factorial(int n) {
	if (n <= 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

int BezierScreen::binominal(int n, int k) {
	if (n < k) {
		return 0;
	}
	auto denominator = (factorial(n - k) * factorial(k));
	if(denominator <= 0) {
		return 0;
	}
	return (factorial(n) / denominator);
}

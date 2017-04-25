#include "bezierscreen.h"
#include <QMatrix4x4>
#include <QDir>
#include <memory>

#define SHADERPATH "/shader/"
#define ZNEAR 0.1f
#define ZFAR 100.0f
#define EYE 0.0f, 0.0f, 2.0f
#define CENTER 0.0f, 0.0f, 0.0f
#define UP 0.0f, 1.0f, 0.0f

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

BezierScreen::BezierScreen(QWidget* parent) : QOpenGLWidget(parent), z_near(ZNEAR), z_far(ZFAR), zoom_factor(1.0f), t(0.0)
{
	this->model = new QMatrix4x4;
	this->view = new QMatrix4x4;
	this->projection = new QMatrix4x4;
	this->prog = new QOpenGLShaderProgram;
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

BezierScreen::~BezierScreen()
{
	makeCurrent();
	delete this->model;
	delete this->view;
	delete this->projection;
	delete this->prog;
}

void BezierScreen::initializeGL()
{
	initializeOpenGLFunctions();
	if (!init_shader())
	{
		qDebug() << this->prog->log();
	}
	this->init_lines();

	glClearColor(GRAY, 0.0);
	this->view->setToIdentity();
	QVector3D eye(EYE);
	this->view->lookAt(eye, {CENTER}, {UP});
}

void BezierScreen::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLineWidth(2);
	glPointSize(7);
	if(lines.isEmpty())
	{
		init_lines();
	}
	for (auto& l : lines)
	{
		l->render_line();
	}
	update();
}

void BezierScreen::resizeGL(int w, int h)
{
	h = h < 1 ? 1 : h;
	glViewport(0, 0, w, h);
	this->projection->setToIdentity();
	this->projection->perspective(45.0f * this->zoom_factor, static_cast<float>(w) / h, this->z_near, this->z_far);
}

void BezierScreen::set_t(int t)
{
	this->t = t/10.0f;
	this->lines.clear();
}

void BezierScreen::init_lines()
{
	std::shared_ptr<Line> start(new Line(this->model, this->view, this->projection, {BLACK},
	                                     QVector<QVector3D>({{0,1,0},{1,2,0},{3,2,0},{4,0,0}})));
	start->setPosition({-2.0f, -1.0f, -10.0f});
	start->setShader(this->prog);
	this->lines.push_back(std::shared_ptr<Line>(start));
	calc_bezier(&*start);

	for (auto& l : lines)
	{
		l->init_line();
	}
}

bool BezierScreen::init_shader() const
{
	QString path = QDir::currentPath() + SHADERPATH;
	QString vert = ".vert";
	QString frag = ".frag";
	if (!this->prog->addShaderFromSourceFile(QOpenGLShader::Vertex, {path + "simple" + vert}))
	{
		return false;
	}
	if (!this->prog->addShaderFromSourceFile(QOpenGLShader::Fragment, {path + "simple" + frag}))
	{
		return false;
	}
	return this->prog->link();
}

void BezierScreen::calc_bezier(Line* next)
{
	QVector3D col[] = {{RED},{GREEN},{MAGENTA}};
	static int col_index = 0;
	QVector<QVector3D> new_line_points;
	for (int i = 0; i < next->size() - 1; i++)
	{
		auto b_i = (1 - this->t) * next->at(i) + t * next->at(i + 1);
		new_line_points.push_back(b_i);
	}

	std::shared_ptr<Line> curr(new Line(this->model, this->view, this->projection, col[col_index++ % 3], new_line_points));
	curr->setPosition({-2.0f, -1.0f, -10.0f});
	curr->setShader(this->prog);
	this->lines.push_back(std::shared_ptr<Line>(curr));
	if (new_line_points.size() > 1)
	{
		calc_bezier(&*curr);
	}
}

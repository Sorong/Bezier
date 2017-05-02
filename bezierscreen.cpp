#include "bezierscreen.h"
#include <QMatrix4x4>
#include <QDir>
#include <QPainter>
#include <QKeyEvent>
#include <memory>

#define SHADERPATH "/shader/"
#define ZNEAR 0.1f
#define ZFAR 100.0f
#define EYE 0.0f, 0.0f, 10.0f
#define CENTER 0.0f, 0.0f, 0.0f
#define UP 0.0f, 1.0f, 0.0f
#define INITPOS 0.0f, 0.0f, -10.0f

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

BezierScreen::BezierScreen(QWidget* parent) : QOpenGLWidget(parent), z_near(ZNEAR), z_far(ZFAR), zoom_factor(1.0f), t(0.0), bezierCurve(nullptr), base(nullptr)
{
	this->model = new QMatrix4x4;
	this->view = new QMatrix4x4;
	this->projection = new QMatrix4x4;
	this->prog = new QOpenGLShaderProgram;
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	//this->coords = { {0.0}, {1,1}, {2,-1}, {4, 3} };
	//this->coords = { {0,0}, {1,1} };
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
	init_baseline();

	glClearColor(GRAY, 0.0);
	this->view->setToIdentity();
	QVector3D eye(EYE);
	this->view->lookAt(eye, {CENTER}, {UP});

}

void BezierScreen::paintGL()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glLineWidth(2);
	glPointSize(7);
	if(coords.isEmpty())
	{
		QPainter painter(this);
		painter.setPen(Qt::darkRed);
		painter.setFont(QFont("Arial", 20));
		painter.drawText(0, 0, width(), height(), Qt::AlignCenter, "Keine Punkte vorhanden!");
		painter.end();
		update();
		return;
	} 
	if(lines.isEmpty())
	{
		init_sublines();
	}
	this->base->render_line();
	for (auto& l : lines)
	{
		l->render_line();
	}
	if(this->bezierCurve != nullptr)
	{
		this->bezierCurve->render_line();
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

void BezierScreen::init_baseline()
{	
	if(this->base != nullptr)
	{
		delete this->base;
	}
	QVector<QVector3D> start_coordinates;
	for (auto& coordinate : this->coords)
	{
		start_coordinates.push_back({ coordinate.x, coordinate.y, 0 });
	}
	this->base = new Line(this->model, this->view, this->projection, { BLUE }, start_coordinates);
	this->base->setPosition({ INITPOS });
	this->base->setShader(this->prog);
	this->base->init_line();
	draw_bezier();
}

void BezierScreen::addCoordinate(float x, float y)
{
	this->addCoordinate({ x,y });
	
}

void BezierScreen::addCoordinate(XY xy)
{
	initializeOpenGLFunctions();
	makeCurrent();
	this->coords.push_back(xy);
	init_baseline();
}


void BezierScreen::removeCoordinateByIndex(int i)
{
	auto coord = coords.at(i);
	coords.removeAt(i);
	makeCurrent();
	init_baseline();
}

void BezierScreen::keyPressEvent(QKeyEvent* event)
{
	switch (event->key()) 
	{
	case Qt::Key_Plus:
		this->zoom_factor /= 1.01;
		this->projection->setToIdentity();
		this->projection->perspective(45.0f * zoom_factor, static_cast<float> (width()) / height(), z_near, z_far);
		break;
	case Qt::Key_Minus:
		zoom_factor = zoom_factor * 1.05 > 3.5 ? zoom_factor : zoom_factor * 1.05;
		this->projection->setToIdentity();
		this->projection->perspective(45.0f * zoom_factor, static_cast<float> (width()) / height(), z_near, z_far);
		break;
	case Qt::Key_Left:
		this->view->rotate(2 * zoom_factor, 0.0, 2, 0);
		break;
	case Qt::Key_Right:
		this->view->rotate(2 * zoom_factor, 0.0, -2, 0);
		break;
	case Qt::Key_Up:
		this->view->rotate(2 * zoom_factor, 2.0, 0, 0);
		break;
	case Qt::Key_Down:
		this->view->rotate(2 * zoom_factor, -2.0, 0, 0);
		break;
	}
}

XY BezierScreen::getCoordinateByIndex(int i)
{
	if(coords.isEmpty() || i > coords.size() - 1)
	{
		return{ 0,0 };
	}
	return coords.at(i);
}

void BezierScreen::init_sublines()
{
	calc_bezier(nullptr);
	for (auto& l : lines)
	{
		l->init_line();
	}

}

void BezierScreen::remove_sublines()
{
	this->lines.clear();
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
	if(next == nullptr)
	{
		next = this->base;
	}
	QVector3D col[] = {{RED},{GREEN},{MAGENTA}};
	static int col_index = 0;
	QVector<QVector3D> new_line_points;
	for (int i = 0; i < next->size() - 1; i++)
	{
		auto b_i = (1 - this->t) * next->at(i) + t * next->at(i + 1);
		new_line_points.push_back(b_i);
	}
	if(new_line_points.isEmpty())
	{
		return;
	}
	std::shared_ptr<Line> curr(new Line(this->model, this->view, this->projection, col[col_index++ % 3], new_line_points));
	curr->setPosition({INITPOS});
	curr->setShader(this->prog);
	this->lines.push_back(std::shared_ptr<Line>(curr));
	if (new_line_points.size() > 1)
	{
		calc_bezier(&*curr);
	} else
	{
		col_index = 0;
	}
}

void BezierScreen::draw_bezier()
{	
	if(this->bezierCurve != nullptr)
	{
		delete this->bezierCurve;
		this->bezierCurve = nullptr;
	}
	QVector<QVector3D> points;
	int n = this->coords.length()-1;
	if (n <= 0) { return; }
	for (float t = 0; static_cast<int>(t*10) <= 10; t+=0.05f)
	{
		QVector<float> bernsteinpolynoms;
		for (int k = 0; k <= n; k++)
		{	
			auto polynom = binominal(n, k) * pow(t, k) * pow(1 - t, n - k);
			bernsteinpolynoms.push_back(polynom);
		}
		QVector3D point(0, 0, 0);
		for (int j = 0; j <= n; j++)
		{
			XY current = this->coords.at(j);
			point += {current.x * bernsteinpolynoms.at(j), current.y * bernsteinpolynoms.at(j), 0};
		}
		points.push_back(point);
	}
	this->bezierCurve = new Line(this->model, this->view, this->projection, { BLACK }, points);
	this->bezierCurve->setPosition({ INITPOS });
	this->bezierCurve->setShader(this->prog);
	this->bezierCurve->init_line();
}

int BezierScreen::factorial(int n)
{	
	if (n <= 1) { return 1; }
	return n * factorial(n-1);
}

int BezierScreen::binominal(int n, int k)
{
	if (n < k) { return 0; }
	return (factorial(n) / (factorial(n - k) * factorial(k)));
}


#ifndef BEZIERSCREEN_H
#define BEZIERSCREEN_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "line.h"
#include <memory>

typedef struct XY {
	float x;
	float y;
} XY;

class BezierScreen : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:


	BezierScreen(QWidget *parent);
	virtual ~BezierScreen();
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	void addCoordinate(float x, float y);
	void addCoordinate(XY xy);
	XY getCoordinateByIndex(int i);
	void removeCoordinateByIndex(int i);
	void keyPressEvent(QKeyEvent* event) override;

public slots:
	void set_t(int t);

private:
	void init_baseline();
	void init_sublines();
	void remove_sublines();
	bool init_shader() const;
	void calc_bezier(Line* next);
	void draw_bezier();
	static int factorial(int n);
	static int binominal(int n, int k);
	QMatrix4x4 *model;
	QMatrix4x4 *view;
	QMatrix4x4 *projection;
	QOpenGLShaderProgram *prog;
	float z_near, z_far, zoom_factor, t;
	Line *base;
	QVector<std::shared_ptr<Line>> lines;
	Line *bezierCurve;
	QVector<XY> coords;
};

#endif // BEZIERSCREEN_H

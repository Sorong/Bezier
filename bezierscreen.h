#ifndef BEZIERSCREEN_H
#define BEZIERSCREEN_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "line.h"
#include <memory>


class BezierScreen : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	BezierScreen(QWidget *parent);
	~BezierScreen();
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

public slots:
	void set_t(int t);

private:
	void init_lines();
	bool init_shader() const;
	void calc_bezier(Line* next);
	QMatrix4x4 *model;
	QMatrix4x4 *view;
	QMatrix4x4 *projection;
	QOpenGLShaderProgram *prog;
	float z_near, z_far, zoom_factor, t;
	QVector<std::shared_ptr<Line>> lines;
};

#endif // BEZIERSCREEN_H

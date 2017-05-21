#ifndef BEZIERSCREEN_H
#define BEZIERSCREEN_H

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "line.h"

class BezierScreen : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

public:


	BezierScreen(QWidget* parent);
	virtual ~BezierScreen();
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	bool addCoordinate(float x, float y);
	bool addCoordinate(QVector4D xy);
	QVector4D getCoordinateByIndex(int i) const;
	void removeCoordinateByIndex(int i);
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	QVector<QVector4D> getBasePoints() const;
	void setT(float t);


public slots:
	void raiseElevation();
	void toggleSublineMode(bool);
	void toggleDerivateMode(bool);

private:
	void initBaseline();
	void initSublines();
	void removeSublines();
	bool initShader() const;
	void calcBezier();
	void drawBezier();
	void drawDerivate();
	void deCasteljau(QVector<QVector4D> &base_coords, QVector<QVector<QVector4D>> &line_coords) const;
	static int factorial(int n);
	static int binominal(int n, int k);

	bool show_sublines_, show_derivate_, highest_grade_reached_;
	QMatrix4x4* model_;
	QMatrix4x4* view_;
	QMatrix4x4* projection_;
	QOpenGLShaderProgram* prog_;
	float z_near_, z_far_, zoom_factor_, t_;
	Line* base_;
	QVector<std::shared_ptr<Line>> lines_;
	Line* bezier_curve_;
	Line* derivate_;
	QVector<QVector4D> coords_;
	float t_drag_;
	QVector4D *dragged_vertex_;
	QVector3D intersect_to_center_;
	Line* ray;
};

#endif // BEZIERSCREEN_H

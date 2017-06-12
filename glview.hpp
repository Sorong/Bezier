#ifndef BEZIERSCREEN_H
#define BEZIERSCREEN_H

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "line.hpp"
#include "beziercalculator.hpp"
#include "beziersurface.hpp"

class GLView : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT

public:


	GLView(QWidget* parent);
	virtual ~GLView();
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
	signals:
	void clickedVertex(QVector4D&);

private:
	bool initShader() const;
	BezierSurface *bezier_surface_;
	bool show_sublines_, show_derivate_, highest_grade_reached_;
	QMatrix4x4 view_, projection_;
	QOpenGLShaderProgram* prog_;
	float z_near_, z_far_, zoom_factor_;
	QVector4D* dragged_vertex_;
	QVector3D intersect_to_center_;
	BezierSurface *surface;
};

#endif // BEZIERSCREEN_H

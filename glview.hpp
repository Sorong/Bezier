#ifndef BEZIERSCREEN_H
#define BEZIERSCREEN_H

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "line.hpp"
#include "beziersurfacecalculator.hpp"
#include "beziersurface.hpp"
#include "glviewcontroller.hpp"




class GLView : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
		friend class GLViewController;
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
	void setS(float s);
	
public slots:
	void degreeElevation();
	void degreeElevationT();
	void degreeElevationS();
	void toggleSublineMode(bool);
	void toggleDerivateMode(bool);
	void modeSelect() const;
	void modeDrawCurve() const;
	void modeDrawSurface() const;
	void modeDrawCoonspatch() const;
	void editClickedVertex();
	signals:
	void clickedVertex(QVector4D*);

private:
	void initModel(Model& model, QVector4D *pos);
	bool initShader() const;
	bool show_sublines_, show_derivate_, highest_grade_reached_;
	QMatrix4x4 view_, projection_, click_model_;
	QOpenGLShaderProgram* prog_;
	float z_near_, z_far_, zoom_factor_;
	GLViewController *controller_;
	BezierSurface *current_surface_;
	QVector<std::shared_ptr<BezierSurface>> surfaces_;
	QVector<std::shared_ptr<BezierSurface>> curves_;
	std::shared_ptr<Model> temp_model_;
};

#endif // BEZIERSCREEN_H

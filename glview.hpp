#ifndef BEZIERSCREEN_H
#define BEZIERSCREEN_H

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "beziersurfacecalculator.hpp"
#include "beziersurface.hpp"
#include "glviewcontroller.hpp"
#include "phongmodel.hpp"
#include "coonspatch.hpp"


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
	void setU(float u);
	void setV(float v);
	
public slots:
	void degreeElevation();
	void degreeElevationU();
	void degreeElevationV();
	void toggleSublineMode(bool);
	void toggleDerivateMode(bool);
	void toggleNormals(bool);
	void modeSelect() const;
	void modeDrawCurve() const;
	void modeDrawSurface() const;
	void modeDrawCoonspatch() const;
	void modeC0() const;
	void setClampedZ(double z) const;
	void editClickedVertex();
	signals:
	void clickedVertex(QVector4D*);
	void clickedSurface(Model *);

private:
	void initModel(Model& model, QVector4D *pos);
	void reinitCurrentSurface();
	bool initShader() const;
	bool initNormalShader() const;
	bool initPhongShader() const;
	bool initTessShader() const;
	bool show_sublines_, show_derivate_, highest_grade_reached_;
	QMatrix4x4 view_, projection_;
	QOpenGLShaderProgram* prog_;
	QOpenGLShaderProgram* normal_prog_;
	QOpenGLShaderProgram* phong_prog_;
	QOpenGLShaderProgram* tess_prog_;
	float z_near_, z_far_, zoom_factor_;
	GLViewController *controller_;
//	BezierSurface *current_surface_;
	QVector3D eye;
	QVector<std::shared_ptr<BezierSurface>> surfaces_;
	QVector<std::shared_ptr<CoonsPatch>> patches_;
	std::shared_ptr<Model> temp_model_;
	Light light;
};

#endif // BEZIERSCREEN_H

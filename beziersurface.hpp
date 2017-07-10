#pragma once
#include "model.hpp"
#include "beziercalculator.hpp"
#include "clickable.hpp"
#include <memory>

class Line;
class BezierCurve;
class Icosahedron;
class TriangleStrip;

class BezierSurface : public Model
{
public:
	BezierSurface(QMatrix4x4& model, const QVector4D &pos);
	~BezierSurface();
	void init(QVector4D *pos = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D *pos = nullptr) override;
	void reinit(QVector4D *pos, bool hardreset);
	void setU(float u);
	void setV(float v);
	void addHorizontalCoordinates(QVector<QVector4D> &coordinates);
	void addVerticalCoordinates(QVector<QVector4D> &coordinates);
	void setCoordinates(QVector4DMatrix& coordinates);
	QVector4DMatrix& getCoordinates();
	QVector4D& get(int index) const;
	int size() const override;
	QVector4D& setClicked(int index) const;
	Clickable& getClicked(int index);
	Clickable& getClicked(int index, int *row, int *col);
	void degreeElevationUV();
	void degreeElevationU();
	void degreeElevationV();
	void showCasteljau(bool state);
	void showDerivate(bool state);
	void removeRow(int row);
	void removeCol(int col);
	void removeRowAndCol(int row, int col);
	void setSurfaceShader(QOpenGLShaderProgram& surface_shader);
	void setDefaultShader(QOpenGLShaderProgram &prog) override;
private:
	void createSubModels();
	void clearSubModels();
	void recalculateSize();
	void createBasePoints();
	void createCurves(QVector4DMatrix& coordinates, QVector4DMatrix& normals);
	void createCasteljauLines();
	void clearAndReinit(QVector4D *pos = nullptr);
	QVector4DMatrix coordinates_;
	QVector4DMatrix normals_;
	QVector<std::shared_ptr<TriangleStrip>> triangle_strips_;
	QVector<std::shared_ptr<Icosahedron>> base_points_;
	QVector<std::shared_ptr<BezierCurve>> curves_;
	QVector<std::shared_ptr<Line>> lines_;
	std::shared_ptr<Line> derivate_line_;
	QOpenGLShaderProgram *surface_shader_;

	float u_, v_;
	int horizontal_size_;
	int vertical_size_;
	bool casteljau_;
	bool derivate_;
};


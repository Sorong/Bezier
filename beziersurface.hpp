#pragma once
#include "model.hpp"
#include "icosahedron.hpp"
#include <memory>
#include "beziercurve.hpp"
#include "trianglestrip.hpp"
#include "line.hpp"
#include "types.hpp"

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
	void degreeElevationUV();
	void degreeElevationU();
	void degreeElevationV();
	void showCasteljau(bool state);
	void showDerivate(bool state);
private:
	void createSubModels();
	void clearSubModels();
	void recalculateSize();
	void createBasePoints();
	void createCurves(QVector4DMatrix& coordinates);
	void createCasteljauLines();
	void clearAndReinit(QVector4D *pos = nullptr);
	QVector4DMatrix coordinates_;
	QVector<std::shared_ptr<TriangleStrip>> triangle_strips_;
	QVector<std::shared_ptr<Icosahedron>> base_points_;
	QVector<std::shared_ptr<BezierCurve>> curves_;
	QVector<std::shared_ptr<Line>> lines_;
	std::shared_ptr<Line> derivate_line_;

	float u_, v_;
	int horizontal_size_;
	int vertical_size_;
	bool casteljau_;
	bool derivate_;
};


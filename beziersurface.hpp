#pragma once
#include "model.hpp"
#include "icosahedron.hpp"
#include <memory>
#include "beziercurve.hpp"
#include "trianglestrip.hpp"
#include "line.hpp"

class BezierSurface : public Model
{
public:
	BezierSurface(QMatrix4x4& model, const QVector4D &pos);
	~BezierSurface();
	void init(QVector4D *pos = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D *pos = nullptr);
	void setT(float t);
	void setS(float s);
	void addHorizontalCoordinates(QVector<QVector4D> &coordinates);
	void addVerticalCoordinates(QVector<QVector4D> &coordinates);
	void setCoordinates(QVector<QVector<QVector4D>> &coordinates);
	QVector<QVector<QVector4D>>& getCoordinates();
	QVector4D& get(int index) const;
	int size() const override;
	QVector4D& setClicked(int index) const;
	void degreeElevation();
	void showCasteljau(bool state);
private:
	void createSubModels();
	void clearSubModels();
	void recalculateSize();
	void createBasePoints();
	void createCurves(QVector<QVector<QVector4D>> &coordinates);
	void createCasteljauLines();
	QVector<QVector<QVector4D>> coordinates_;
	QVector<std::shared_ptr<TriangleStrip>> triangle_strips_;
	QVector<std::shared_ptr<Icosahedron>> base_points_;
	QVector<std::shared_ptr<BezierCurve>> curves_;
	QVector<std::shared_ptr<Line>> lines_;

	float t_, s_;
	int horizontal_size_;
	int vertical_size_;
	bool casteljau_;
	bool derivate;
};


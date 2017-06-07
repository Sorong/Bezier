#pragma once
#include "model.hpp"
#include "icosahedron.hpp"
#include <memory>
#include "beziercurve.hpp"
#include "trianglestrip.hpp"

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
	QVector4D* get(int index) const;
	int size() const override;
	void setClicked(int index) const;
private:
	QVector<QVector<QVector4D>> coordinates_;
	QVector<std::shared_ptr<TriangleStrip>> triangle_strips_;
	QVector<std::shared_ptr<Icosahedron>> base_points_;
	QVector<std::shared_ptr<BezierCurve>> curves_;

	float t_, s_;
};


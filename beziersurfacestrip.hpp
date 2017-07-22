#pragma once
#include "model.hpp"
#include "beziercurve.hpp"
#include "phongmodel.hpp"

class BezierSurfaceStrip : public Model, public PhongModel {
public:
	BezierSurfaceStrip(QMatrix4x4& model, BezierCurve* first_curve, BezierCurve* second_curve, Light& light);
	BezierSurfaceStrip(QMatrix4x4& model, const QVector4D& pos, BezierCurve* first_curve, BezierCurve* second_curve, Light& light);
	void init(QVector4D* position) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D* pos) override;
	void setFirstCurve(BezierCurve* first);
	void setSecondCurve(BezierCurve* second);
private:
	BezierCurve *first_curve_;
	BezierCurve *second_curve_;
};

#pragma once
#include <QVector>
#include <QVector4D>
#include "beziercalculator.hpp"

class BezierSurfaceCalculator : public BezierCalculator
{
public:
	BezierSurfaceCalculator();
	~BezierSurfaceCalculator();
	void deCasteljauSurface(const QVector<QVector<QVector4D>>& base_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float t, float s);
	bool bezierSurface(QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float precision) const;
	bool bezierSurface(QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float precision_t, float precision_s) const;
	QVector<QVector4D> derivateSurface(const QVector<QVector<QVector4D>> &src_coordinates, float t, float s, QVector4D* derivate_root = nullptr);
	void degreeElevationSurface(QVector<QVector<QVector4D>> &src_coordinates) const;
	void degreeElevationTSurface(QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>>* dest = nullptr) const;
	void degreeElevationSSurface(QVector<QVector<QVector4D>> &src_coodinates, QVector<QVector<QVector4D>>* dest = nullptr) const;
	QVector4D calculateDerivateSurface(QVector<QVector<QVector4D>> &src_coordinates, float t, float s);
private:
	void horizontalToVertical(const QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates) const;
	

};


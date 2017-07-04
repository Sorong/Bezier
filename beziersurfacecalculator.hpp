#pragma once
#include <QVector>
#include <QVector4D>
#include "beziercalculator.hpp"

class BezierSurfaceCalculator : public BezierCalculator
{
public:
	BezierSurfaceCalculator();
	~BezierSurfaceCalculator();
	void deCasteljauSurface(const QVector4DMatrix& base_coordinates, QVector4DMatrix& dest_coordinates, float t, float s);
	bool bezierSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates, float precision) const;
	bool bezierSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates, float precision_t, float precision_s) const;
	QVector<QVector4D> derivateSurface(const QVector4DMatrix& src_coordinates, float t, float s, QVector4D* derivate_root = nullptr);
	void degreeElevationSurface(QVector4DMatrix& src_coordinates) const;
	void degreeElevationTSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix* dest = nullptr) const;
	void degreeElevationSSurface(QVector4DMatrix& src_coodinates, QVector4DMatrix* dest = nullptr) const;
	QVector4D calculateDerivateSurface(QVector4DMatrix& src_coordinates, float t, float s);
private:
	void horizontalToVertical(const QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates) const;
	

};


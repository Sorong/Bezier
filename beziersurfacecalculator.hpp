#pragma once
#include <QVector>
#include <QVector4D>
#include "beziercalculator.hpp"

class BezierSurfaceCalculator : public BezierCalculator
{
public:
	BezierSurfaceCalculator();
	~BezierSurfaceCalculator();
	void deCasteljauSurface(const QVector4DMatrix& base_coordinates, QVector4DMatrix& dest_coordinates, float u, float v) const;
	bool bezierSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates, float precision) const;
	bool bezierSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates, float precision_u, float precision_v) const;
	QVector<QVector4D> derivateSurface(const QVector4DMatrix& src_coordinates, float u, float v, QVector4D* derivate_root = nullptr) const;
	void degreeElevationSurface(QVector4DMatrix& src_coordinates) const;
	void degreeElevationUSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix* dest = nullptr) const;
	void degreeElevationVSurface(QVector4DMatrix& src_coodinates, QVector4DMatrix* dest = nullptr) const;
	void normalsSurface(const QVector4DMatrix& src_coordinates, QVector4DMatrix &dest_normals, float precision_u, float precision_v) const;
private:
	void horizontalToVertical(const QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates) const;
	

};


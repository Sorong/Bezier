#pragma once
#include <QVector>
#include <QVector4D>

class BezierCalculator
{
public:
	BezierCalculator();
	~BezierCalculator();
	void deCasteljau(QVector<QVector4D> &base_coordinates, QVector<QVector<QVector4D>> &line_coordinates, float t) const;
	bool calculateBeziercurve(QVector<QVector4D>& src_coordinates, QVector<QVector4D>& dest_coordinates, float precision) const;
	bool calculateBezierSurface(QVector<QVector<QVector4D>> &src_coordiantes, QVector<QVector<QVector4D>> &dest_coordinates, float precision) const;
	bool calculateBezierSurface(QVector<QVector<QVector4D>> &src_coordiantes, QVector<QVector<QVector4D>> &dest_coordinates, float precision_t, float precision_s) const;
	QVector4D calculateDerivate(QVector<QVector4D>& src_coordinates, float t) const;
	void degreeElevationSurface(QVector<QVector<QVector4D>> &src_coordinates) const;
	void degreeElevation(QVector<QVector4D>& src_coordinates) const;
	QVector4D calculateDerivateSurface(QVector<QVector<QVector4D>> &src_coordinates, float t, float s);
private:
	int factorial(int n) const;
	int binominal(int n, int k) const;
};


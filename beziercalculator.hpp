#pragma once
#include <QVector>
#include <QVector4D>

class BezierCalculator
{
public:
	BezierCalculator();
	~BezierCalculator();
	void deCasteljau(const QVector<QVector4D>& base_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float t) const;
	void deCasteljauSurface(const QVector<QVector<QVector4D>>& base_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float t, float s);
	bool bezierCurve(QVector<QVector4D>& src_coordinates, QVector<QVector4D>& dest_coordinates, float precision) const;
	bool bezierSurface(QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float precision) const;
	bool bezierSurface(QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float precision_t, float precision_s) const;
	QVector4D derivate(const QVector<QVector4D>& src_coordinates, float t) const;
	QVector<QVector4D> derivateSurface(const QVector<QVector<QVector4D>> &src_coordinates, float t, float s, QVector4D* derivate_root = nullptr);
	void degreeElevationSurface(QVector<QVector<QVector4D>> &src_coordinates) const;
	void degreeElevation(QVector<QVector4D>& src_coordinates) const;
	QVector4D calculateDerivateSurface(QVector<QVector<QVector4D>> &src_coordinates, float t, float s);
private:
	void horizontalToVertical(const QVector<QVector<QVector4D>> &src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates) const;
	void bezierBernstein(const QVector<QVector4D> &src_coordinates, QVector<QVector4D> &dest_coordinates, float t);
	int factorial(int n) const;
	int binominal(int n, int k) const;
};


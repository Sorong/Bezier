#pragma once
#include <QVector>
#include <QVector4D>

class BezierCalculator
{
public:
	BezierCalculator();
	~BezierCalculator();
	void deCasteljau(const QVector<QVector4D>& base_coordinates, QVector<QVector<QVector4D>> &dest_coordinates, float t) const;
	bool bezierCurve(QVector<QVector4D>& src_coordinates, QVector<QVector4D>& dest_coordinates, float precision) const;
	QVector4D derivate(const QVector<QVector4D>& src_coordinates, float t) const;
	void degreeElevation(QVector<QVector4D>& src_coordinates) const;
protected:
	void bezierBernstein(const QVector<QVector4D> &src_coordinates, QVector<QVector4D> &dest_coordinates, float t);
	int factorial(int n) const;
	int binominal(int n, int k) const;
};


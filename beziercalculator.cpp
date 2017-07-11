#include "beziercalculator.hpp"
#define BERNSTEINLIMIT 13


BezierCalculator::BezierCalculator()
{
}


BezierCalculator::~BezierCalculator()
{
}

void BezierCalculator::deCasteljau(const QVector<QVector4D>& base_coordinates, QVector4DMatrix& dest_coordinates, float u) const {
	if (base_coordinates.isEmpty()) {
		return;
	}
	QVector<QVector4D> new_line_points;
	for (int i = 0; i < base_coordinates.size() - 1; i++) {
		auto b_i = (1 - u) * base_coordinates.at(i) + u * base_coordinates.at(i + 1);
		new_line_points.push_back(b_i);
	}
	if (new_line_points.isEmpty()) {
		return;
	}
	dest_coordinates.push_back(new_line_points);
	if (new_line_points.size() > 1) {
		deCasteljau(new_line_points, dest_coordinates, u);
	}
}

bool BezierCalculator::bezierCurve(QVector<QVector4D>& src_coordinates, QVector<QVector4D>& dest_coordinates, float precision) const {
	if (src_coordinates.size() < 2) {
		dest_coordinates = src_coordinates;
		return true;
	}
	auto n = src_coordinates.size() - 1;
	for (auto tAsInt = 0; tAsInt <= 100; tAsInt += (precision * 100)) {
		double t = tAsInt / 100.f;
		QVector<double> bernsteinpolynoms;
		double beziertest = 0;
		if(n >= BERNSTEINLIMIT) {
			QVector4DMatrix mat;
			deCasteljau(src_coordinates, mat, t);
			dest_coordinates.push_back(mat.last().last());
			continue;
		}
		for (int k = 0; k <= n; k++) {
			double polynom = binominal(n, k) * pow(t, k) * pow(1 - t, n - k);
			beziertest += (polynom);
			bernsteinpolynoms.push_back(polynom);

		}
		if (beziertest <= 0.99) {
			return false;
		}
		QVector4D point(0, 0, 0, 0);
		for (auto j = 0; j <= n; j++) {
			auto current = src_coordinates.at(j);
			point += current * bernsteinpolynoms.at(j);
		}
		dest_coordinates.push_back(point);
	}
	return true;
}

QVector4D BezierCalculator::derivate(const QVector<QVector4D>& src_coordinates, float t) const {
	QVector<float> bernsteinpolynoms;
	if(src_coordinates.size() >= BERNSTEINLIMIT) {
		QVector4DMatrix mat;
		deCasteljau(src_coordinates, mat, t);
		QVector4D derivate;
		if (t <= 0) {
			derivate = mat[0][1] - mat.last().last();
		} else if(t >= 1) {
			derivate = mat.last().last() - mat[mat.size() - 2][0];
		} else {
			derivate = mat[mat.size() - 2].last() - mat.last().last();
		}
		return derivate;
	}
	auto n = src_coordinates.size() - 1;
	for (auto j = 0; j < n; j++) {
		auto polynom = binominal((n - 1), j) * pow(t, j) * pow(1 - t, (n - 1) - j);
		bernsteinpolynoms.push_back(polynom);
	}

	QVector4D derivate(0, 0, 0, 0);
	for (auto j = 0; j < src_coordinates.size() - 1; j++) {
		auto b1 = src_coordinates.at(j + 1);
		auto b2 = src_coordinates.at(j);
		auto current = b1 - b2;
		derivate += current * bernsteinpolynoms.at(j);
	}
	return derivate;
}

void BezierCalculator::degreeElevation(QVector<QVector4D>& src_coordinates) const {
	QVector<QVector4D> new_coordinates;
	new_coordinates.push_back(src_coordinates.at(0));
	for (int i = 1, n = src_coordinates.size() - 1; i < src_coordinates.size(); i++) {
		QVector4D new_b = static_cast<float>(i) / (n + 1) * src_coordinates.at(i - 1) + (1 - static_cast<float>(i) / (n + 1)) * src_coordinates.at(i);
		new_coordinates.push_back(new_b);
	}
	new_coordinates.push_back(src_coordinates.at(src_coordinates.size() - 1));
	src_coordinates = new_coordinates;
}

void BezierCalculator::bezierBernstein(const QVector<QVector4D>& src_coordinates, QVector<QVector4D>& dest_coordinates, float v) const {
	auto n = src_coordinates.size() - 1;
	QVector<float> bernsteinpolynoms;
	float beziertest = 0;
	for (int k = 0; k <= n; k++) {
		auto polynom = binominal(n, k) * pow(v, k) * pow(1 - v, n - k);
		beziertest += polynom;
		bernsteinpolynoms.push_back(polynom);

	}
	if (beziertest * 100 <= 99) {
		throw std::out_of_range("Invalid bezier calculation");
	}
	QVector4D point(0, 0, 0, 0);
	for (auto j = 0; j <= n; j++) {
		auto current = src_coordinates.at(j);
		point += current * bernsteinpolynoms.at(j);
	}
	dest_coordinates.push_back(point);
}

long BezierCalculator::factorial(int n) const {
	if (n <= 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

long BezierCalculator::binominal(int n, int k) const {
	if (n < k) {
		return 0;
	}
	auto denominator = (factorial(n - k) * factorial(k));
	if (denominator <= 0) {
		return 0;
	}
	return (factorial(n) / denominator);
}

#include "beziercalculator.hpp"



BezierCalculator::BezierCalculator()
{
}


BezierCalculator::~BezierCalculator()
{
}

void BezierCalculator::deCasteljau(const QVector<QVector4D>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float t) const {
	if (src_coordinates.isEmpty()) {
		return;
	}
	QVector<QVector4D> new_line_points;
	for (int i = 0; i < src_coordinates.size() - 1; i++) {
		auto b_i = (1 - t) * src_coordinates.at(i) + t * src_coordinates.at(i + 1);
		new_line_points.push_back(b_i);
	}
	if (new_line_points.isEmpty()) {
		return;
	}
	dest_coordinates.push_back(new_line_points);
	if (new_line_points.size() > 1) {
		deCasteljau(new_line_points, dest_coordinates, t);
	}
}

void BezierCalculator::deCasteljauSurface(const QVector<QVector<QVector4D>>& base_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float t, float s) {
	if(base_coordinates.size() <= 1) {
		deCasteljau(base_coordinates.at(0), dest_coordinates, t);
		return;
	}
	QVector<QVector4D> vertical_coordinates;
	for(auto& vec : base_coordinates) {
		deCasteljau(vec, dest_coordinates, t);
		vertical_coordinates.push_back(dest_coordinates.last().last());
	}
	dest_coordinates.push_back(vertical_coordinates);
	deCasteljau(vertical_coordinates, dest_coordinates, s);
}


bool BezierCalculator::calculateBeziercurve(QVector<QVector4D>& src_coordinates, QVector<QVector4D>& dest_coordinates, float precision) const {
	if(src_coordinates.size() <= 2) {
		dest_coordinates = src_coordinates;
		return true;
	}
	auto n = src_coordinates.size() - 1;
	for (auto tAsInt = 0; tAsInt <= 100; tAsInt+=(precision*100)) {
		auto t = tAsInt / 100.f;
		QVector<float> bernsteinpolynoms;
		float beziertest = 0;
		for (int k = 0; k <= n; k++) {
			auto polynom = binominal(n, k) * pow(t, k) * pow(1 - t, n - k);
			beziertest += polynom;
			bernsteinpolynoms.push_back(polynom);

		}
		if (beziertest * 100 <= 99) {
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
bool BezierCalculator::calculateBezierSurface(QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float precision_t, float precision_s) const {
	QVector<QVector<QVector4D>> temp;
	for (auto& current : src_coordinates) {
		QVector<QVector4D> temp_dest;
		if (!calculateBeziercurve(current, temp_dest, precision_t)) {
			dest_coordinates = src_coordinates;
			return false;
		}
		temp.push_back(temp_dest);
	}
	if(temp.size() == 1)
	{
		dest_coordinates = temp;
	}
	for (int i = 0; i < temp.at(0).size(); i++) {
		QVector<QVector4D> bezier_t;
		for (int j = 0; j < temp.size(); j++) {
			bezier_t.push_back(temp.at(j).at(i));
		}
		QVector<QVector4D> bezier_s;
		if(!calculateBeziercurve(bezier_t, bezier_s, precision_s)) {
			dest_coordinates = src_coordinates;
			return false;
		}
		dest_coordinates.push_back(bezier_s);
	}
	return true;
}

	bool BezierCalculator::calculateBezierSurface(QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float precision) const
	{
        return calculateBezierSurface(src_coordinates, dest_coordinates, precision, precision);
	}
	



QVector4D BezierCalculator::calculateDerivate(QVector<QVector4D>& src_coordinates, float t) const {
	QVector<QVector4D> points;
	QVector<float> bernsteinpolynoms;

	auto n = src_coordinates.size() - 1;
	for (auto j = 0; j < n; j++) {
		auto polynom = binominal((n - 1), j) * pow(t, j) * pow(1 - t, (n - 1) - j);
		bernsteinpolynoms.push_back(polynom);
	}

	QVector4D derivate(0, 0, 0, 0);
	for (auto j = 0; j < src_coordinates.size() - 1; j++) {
		auto b1 = src_coordinates.at(j + 1);
		auto b2 = src_coordinates.at(j);
		auto current = (b1 / b1.w()) - (b2 / b2.w());
		derivate += current * bernsteinpolynoms.at(j);
	}
	return derivate;
}

void BezierCalculator::degreeElevationSurface(QVector<QVector<QVector4D>>& src_coordinates) const {
	if (src_coordinates.isEmpty()) {
		return;
	} 
	QVector<QVector<QVector4D>> horizontalElevation;
	for (int i = 0; i < src_coordinates.size(); i++) {
		QVector<QVector4D> elevation = src_coordinates.at(i);
		degreeElevation(elevation);
		horizontalElevation.push_back(elevation);
	}
	if(horizontalElevation.size() <= 1)	{
		src_coordinates = horizontalElevation;
		return;
	}
	QVector<QVector<QVector4D>> verticalElevation;
	horizontalToVertical(horizontalElevation, verticalElevation);
	src_coordinates.resize(src_coordinates.size() + 1);
	for(int i = 0; i < src_coordinates.size(); i++) {
		int j = 0;
		for(; j < verticalElevation.size(); j++) {
			if(src_coordinates[i].isEmpty() || (src_coordinates[i].size() <= j)) {
				src_coordinates[i].push_back(verticalElevation[j][i]);
			} else {
				src_coordinates[i][j] = verticalElevation[j][i];
			}
			
		}
	}
}

void BezierCalculator::degreeElevation(QVector<QVector4D>& src_coordinates) const {
	QVector<QVector4D> new_coordinates;
	new_coordinates.push_back(src_coordinates.at(0));
	for (int i = 1, n = src_coordinates.size() - 1; i < src_coordinates.size(); i++) {
		QVector4D new_b = static_cast<float>(i) / (n + 1) * src_coordinates.at(i - 1) + (1 - static_cast<float>(i) / (n + 1)) * src_coordinates.at(i);
		//new_b /= new_b.w();
		new_coordinates.push_back(new_b);
	}
	new_coordinates.push_back(src_coordinates.at(src_coordinates.size() - 1));
	src_coordinates = new_coordinates;
}

void BezierCalculator::horizontalToVertical(const QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates) const {
	if(src_coordinates.isEmpty() || src_coordinates.at(0).isEmpty()) {
		return;
	}
	for (int k = 0; k < src_coordinates.at(0).size(); k++) {
		QVector<QVector4D> elevation;
		for (int i = 0; i < src_coordinates.size(); i++) {
			elevation.push_back(src_coordinates.at(i).at(k));

		}
		degreeElevation(elevation);
		dest_coordinates.push_back(elevation);
	}
}

int BezierCalculator::factorial(int n) const {
	if (n <= 1) {
		return 1;
	}
	return n * factorial(n - 1);
}

int BezierCalculator::binominal(int n, int k) const {
	if (n < k) {
		return 0;
	}
	auto denominator = (factorial(n - k) * factorial(k));
	if (denominator <= 0) {
		return 0;
	}
	return (factorial(n) / denominator);
}

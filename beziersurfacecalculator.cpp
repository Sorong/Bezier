#include "beziersurfacecalculator.hpp"
#include <QVector3D>


BezierSurfaceCalculator::BezierSurfaceCalculator()
{
}


BezierSurfaceCalculator::~BezierSurfaceCalculator()
{
}

void BezierSurfaceCalculator::deCasteljauSurface(const QVector<QVector<QVector4D>>& base_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float t, float s) {
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


bool BezierSurfaceCalculator::bezierSurface(QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float precision_t, float precision_s) const {
	QVector<QVector<QVector4D>> temp;
	for (auto& current : src_coordinates) {
		QVector<QVector4D> temp_dest;
		if (!bezierCurve(current, temp_dest, precision_t)) {
			dest_coordinates = src_coordinates;
			return false;
		}
		temp.push_back(temp_dest);
	}
	if(temp.size() == 1)
	{
		dest_coordinates = temp;
		return true;
	}
	for (int i = 0; i < temp.at(0).size(); i++) {
		QVector<QVector4D> bezier_t;
		for (int j = 0; j < temp.size(); j++) {
			bezier_t.push_back(temp.at(j).at(i));
		}
		QVector<QVector4D> bezier_s;
		if(!bezierCurve(bezier_t, bezier_s, precision_s)) {
			dest_coordinates = src_coordinates;
			return false;
		}
		dest_coordinates.push_back(bezier_s);
	}
	return true;
}

	bool BezierSurfaceCalculator::bezierSurface(QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates, float precision) const
	{
        return bezierSurface(src_coordinates, dest_coordinates, precision, precision);
	}
	
QVector<QVector4D> BezierSurfaceCalculator::derivateSurface(const QVector<QVector<QVector4D>>& src_coordinates, float t, float s, QVector4D* derivate_root) {
	if(src_coordinates.isEmpty()) {
		return {};
	}
	if(src_coordinates.size() == 1) {
		if(derivate_root) {
			QVector<QVector<QVector4D>> dest;
			deCasteljau(src_coordinates.at(0), dest, t);
			*derivate_root = dest.last().last();
			*derivate_root /= derivate_root->w();
		}
		return { derivate(src_coordinates.at(0), t).normalized() };
	}
	QVector<QVector4D> s_direction;
	for(auto& curve : src_coordinates) {
		bezierBernstein(curve, s_direction, t);
	}
	QVector4D s_derivate = derivate(s_direction, s);
	QVector<QVector<QVector4D>> vertical;
	QVector<QVector4D> t_direction;
	horizontalToVertical(src_coordinates, vertical);
	for(auto& curve : vertical) {
		bezierBernstein(curve, t_direction, s);
	}
	QVector4D t_derivate = derivate(t_direction, t);
	if(derivate_root) {
		QVector<QVector<QVector4D>> dest;
		deCasteljau(s_direction, dest, s);
		*derivate_root = dest.last().last();
	}
	QVector<QVector4D> return_value;
	if(t != 1) {
		return_value.push_back(t_derivate.toVector3D().normalized());
	}
	if(s != 1) {
		return_value.push_back(s_derivate.toVector3D().normalized());
	}
	return return_value;
}


void BezierSurfaceCalculator::degreeElevationSurface(QVector<QVector<QVector4D>>& src_coordinates) const {
	if (src_coordinates.isEmpty()) {
		return;
	} 
	QVector<QVector<QVector4D>> horizontal_elevation;
	degreeElevationTSurface(src_coordinates, &horizontal_elevation);
	if(horizontal_elevation.size() <= 1)	{
		src_coordinates = horizontal_elevation;
		return;
	}
	
	QVector<QVector<QVector4D>> vertical_elevation;
	degreeElevationSSurface(src_coordinates, &vertical_elevation);
	src_coordinates = vertical_elevation;
}

void BezierSurfaceCalculator::degreeElevationTSurface(QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>* dest) const {
	if(!dest) {
		dest = &src_coordinates;
	}
	for (int i = 0; i < src_coordinates.size(); i++) {
		QVector<QVector4D> elevation = src_coordinates.at(i);
		degreeElevation(elevation);
		if(dest == &src_coordinates) {
			dest->replace(i, elevation);
		} else {
			dest->insert(i, elevation);
		}
	
	}
}

void BezierSurfaceCalculator::degreeElevationSSurface(QVector<QVector<QVector4D>>& src_coodinates, QVector<QVector<QVector4D>>* dest) const {
	if(!dest) {
		dest = &src_coodinates;
	}
	QVector<QVector<QVector4D>> elevation;
	horizontalToVertical(src_coodinates, elevation);
	dest->resize(src_coodinates.size() + 1);
	for (int i = 0; i < dest->size(); i++) {
		int j = 0;
		for (; j < elevation.size(); j++) {
			if ((*dest)[i].isEmpty() || ((*dest)[i].size() <= j)) {
				(*dest)[i].push_back(elevation[j][i]);
			}
			else {
				(*dest)[i][j] = elevation[j][i];
			}

		}
	}
}

void BezierSurfaceCalculator::horizontalToVertical(const QVector<QVector<QVector4D>>& src_coordinates, QVector<QVector<QVector4D>>& dest_coordinates) const {
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


#include "beziersurfacecalculator.hpp"
#include <QVector3D>


BezierSurfaceCalculator::BezierSurfaceCalculator() {
}


BezierSurfaceCalculator::~BezierSurfaceCalculator() {
}

void BezierSurfaceCalculator::deCasteljauSurface(const QVector4DMatrix& base_coordinates, QVector4DMatrix& dest_coordinates, float u, float v) const {
	if(base_coordinates.size() <= 1) {
		deCasteljau(base_coordinates.at(0), dest_coordinates, u);
		return;
	}
	QVector<QVector4D> vertical_coordinates;
	for(auto& vec : base_coordinates) {
		deCasteljau(vec, dest_coordinates, u);
		vertical_coordinates.push_back(dest_coordinates.last().last());
	}
	dest_coordinates.push_back(vertical_coordinates);
	deCasteljau(vertical_coordinates, dest_coordinates, v);
}


bool BezierSurfaceCalculator::bezierSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates, float precision_u, float precision_v) const {
	QVector4DMatrix temp;
	for (auto& current : src_coordinates) {
		QVector<QVector4D> temp_dest;
		if (!bezierCurve(current, temp_dest, precision_u)) {
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
		if(!bezierCurve(bezier_t, bezier_s, precision_v)) {
			dest_coordinates = src_coordinates;
			return false;
		}
		dest_coordinates.push_back(bezier_s);
	}
	return true;
}

	bool BezierSurfaceCalculator::bezierSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates, float precision) const
	{
        return bezierSurface(src_coordinates, dest_coordinates, precision, precision);
	}
	
QVector<QVector4D> BezierSurfaceCalculator::derivateSurface(const QVector4DMatrix& src_coordinates, float u, float v, QVector4D* derivate_root) const {
	if(src_coordinates.isEmpty()) {
		return {};
	}
	if(src_coordinates.size() == 1) {
		if(derivate_root) {
			QVector4DMatrix dest;
			deCasteljau(src_coordinates.at(0), dest, u);
			*derivate_root = dest.last().last();
			*derivate_root /= derivate_root->w();
		}
		return { derivate(src_coordinates.at(0), u).normalized() };
	}
	QVector<QVector4D> s_direction;
	for(auto& curve : src_coordinates) {
		bezierBernstein(curve, s_direction, u);
	}
	QVector4D s_derivate = derivate(s_direction, v);
	QVector4DMatrix vertical;
	QVector<QVector4D> t_direction;
	horizontalToVertical(src_coordinates, vertical);
	for(auto& curve : vertical) {
		bezierBernstein(curve, t_direction, v);
	}
	QVector4D t_derivate = derivate(t_direction, u);
	if(derivate_root) {
		QVector4DMatrix dest;
		deCasteljau(s_direction, dest, v);
		*derivate_root = dest.last().last();
	}
	QVector<QVector4D> return_value;
	return_value.push_back(t_derivate.toVector3D().normalized());
	return_value.push_back(s_derivate.toVector3D().normalized());
	return return_value;
}


void BezierSurfaceCalculator::degreeElevationSurface(QVector4DMatrix& src_coordinates) const {
	if (src_coordinates.isEmpty()) {
		return;
	} 
	QVector4DMatrix horizontal_elevation;
	degreeElevationUSurface(src_coordinates, &horizontal_elevation);
	if(horizontal_elevation.size() <= 1)	{
		src_coordinates = horizontal_elevation;
		return;
	}
	
	QVector4DMatrix vertical_elevation;
	degreeElevationVSurface(horizontal_elevation, &vertical_elevation);
	src_coordinates = vertical_elevation;
}

void BezierSurfaceCalculator::degreeElevationUSurface(QVector4DMatrix& src_coordinates, QVector4DMatrix* dest) const {
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

void BezierSurfaceCalculator::degreeElevationVSurface(QVector4DMatrix& src_coodinates, QVector4DMatrix* dest) const {
	if(!dest) {
		dest = &src_coodinates;
	}
	QVector4DMatrix elevation;
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

void BezierSurfaceCalculator::normalsSurface(const QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_normals, float precision_u, float precision_v) const {
	if(src_coordinates.size() <= 1) {
		return;
	}
	for (auto tAsInt = 0; tAsInt <= 100; tAsInt += (precision_u * 100)) {
		QVector<QVector4D> u_dir_normals;
		for(auto vAsInt = 0; vAsInt <= 100; vAsInt += (precision_v * 100)) {
			QVector<QVector4D> derivate = derivateSurface(src_coordinates, tAsInt / 100.0f, vAsInt / 100.0f);
			QVector3D normal = QVector3D::crossProduct(derivate[1].toVector3D(), derivate[0].toVector3D()).normalized();
			u_dir_normals.push_back({ normal });
		}
		dest_normals.push_back(u_dir_normals);
	}
}

void BezierSurfaceCalculator::horizontalToVertical(const QVector4DMatrix& src_coordinates, QVector4DMatrix& dest_coordinates) const {
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


#include "phongmodel.hpp"



PhongModel::PhongModel(Light& light): light_(&light) {
}


PhongModel::~PhongModel()
{
}

void PhongModel::setLight(Light& light) {
	this->light_ = &light;
}

void PhongModel::setMaterial(Material& material) {
	this->material_ = material;
}

void PhongModel::setMaterial(QVector4D& material) {
	this->material_.ambient = material;
	this->material_.diffuse = material;
	this->material_.specular = { 1,1,1,1 };
	this->material_.shininess = 100.0f;
}

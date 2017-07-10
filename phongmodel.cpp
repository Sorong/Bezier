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

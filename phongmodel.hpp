#pragma once
#include <QVector4D>

typedef struct Light {
	QVector4D pos;
	QVector4D ambient;
	QVector4D diffuse;
	QVector4D specular;
} Light;

typedef struct Material {
	QVector4D diffuse;
	QVector4D ambient;
	QVector4D specular;
	float shininess;
} Material;

class PhongModel
{
public:
	explicit PhongModel(Light& light);
	virtual ~PhongModel();
	void setLight(Light& light);
	void setMaterial(Material& material);
	void setMaterial(QVector4D& material);
protected:
	Light *light_;
	Material material_;
};


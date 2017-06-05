#pragma once
#include "model.hpp"

class Icosahedron : public Model {
public:
	Icosahedron();
	Icosahedron(const Icosahedron &) = delete;
	Icosahedron& operator= (const Icosahedron& other) = delete;
	Icosahedron(QMatrix4x4& model, const QVector4D* reference_vertex);
	~Icosahedron();
	void init(QVector4D* pos = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void setModelMatrix(QMatrix4x4& model);
	void setRadius(float i);
	void setColor(QVector3D color);
	void scale(float ratio);
	const QVector4D* getReference() const;
private:
	const QVector4D* reference_vertex_;
	QVector3D color_;
	float radius_;
};

#pragma once
#include "model.hpp"

class Icosahedron : public Model {
public:
	Icosahedron();
	Icosahedron(const Icosahedron &) = delete;
	Icosahedron& operator= (const Icosahedron& other) = delete;
	Icosahedron(QMatrix4x4& model, QVector4D* reference_vertex);
	~Icosahedron();
	void init(QVector4D* pos = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit();
	void setRadius(float i);
	void setColor(QVector4D color);
	void scale(float ratio);
	void translateToReference();
	QVector4D* getReference() const;
private:
	QVector4D* reference_vertex_;
	QVector4D color_;
	float radius_;
};

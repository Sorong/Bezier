#pragma once
#include "model.hpp"
#include "icosahedron.hpp"
#include <memory>

class Rectangle : public Model, public Clickable
{
public:
	Rectangle() = delete;
	Rectangle(QVector4D start, int size);
	~Rectangle();
	void init(QVector4D* position) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D* position) override;
	void setColor(QVector4D color) override;
	void translateToReference() override;
	void setClicked(QVector4D& color) override;
	void setUnclicked(QVector4D& color) override;
};


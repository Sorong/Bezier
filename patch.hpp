#pragma once
#include "model.hpp"
#include "beziercalculator.hpp"

class Patch : public Model
{
public:
	Patch(QMatrix4x4& model, const QVector4D& pos);
	~Patch();
	void init(QVector4D* position = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D *position = nullptr) override;
	void setCoordinates(QVector4DMatrix& coordinates);
private:
	QVector4DMatrix* patch_coordinates_;
};


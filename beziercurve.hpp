#pragma once
#include "model.hpp"
class BezierCurve : public Model
{
public:
	BezierCurve(QMatrix4x4 &model, const QVector4D pos);
	BezierCurve(QMatrix4x4& model);
	~BezierCurve();
	void setBaseCoordinates(QVector<QVector4D> *coordinates);
	QVector<QVector4D>& getVertices();
	void init(QVector4D* position = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	int size() const override;
	void setColor(QVector3D color);
	void setModelMatrix(QMatrix4x4& model);
private:
	QVector<QVector4D> *coordinates_;
};


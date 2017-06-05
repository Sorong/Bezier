#pragma once
#include "model.hpp"
#include "icosahedron.hpp"
#include <memory>

class BezierSurface : public Model
{
public:
	BezierSurface(QMatrix4x4& model, const QVector4D &pos);
	~BezierSurface();
	void init(QVector4D *pos = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D *pos = nullptr);
	void setT(float t);
	void setS(float s);
	void addCoordinates(QVector<QVector4D> coordinates);
	void setCoordinates(QVector < QVector<QVector4D>> coordinates);
	const QVector4D* get(int index) const;
	int size();
private:
	QVector<QVector<QVector4D>> coordinates_;
	QVector<std::shared_ptr<Icosahedron>> base_points_;
	float t_, s_;
};


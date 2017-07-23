#pragma once
#include "phongmodel.hpp"
#include "model.hpp"
#include "beziercurve.hpp"
#include <memory>
#include "icosahedron.hpp"
#include "beziercalculator.hpp"

class CoonsPatch : public Model
{
public:
	CoonsPatch(QMatrix4x4& model, const QVector4D& pos);
	~CoonsPatch();
	void init(QVector4D* position) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void reinit(QVector4D *pos = nullptr) override;
	void setCoordinates(QVector4DMatrix& coordinates);
	void degreeElevation();
	Clickable& getClicked(int index);
	QVector4D& get(int index) const;
	int size() const override;
private:
	void createSubModels();
	void createBasePoints();
	void createCurves();
	QVector<std::shared_ptr<Icosahedron>> base_points_;
	QVector<std::shared_ptr<BezierCurve>> curves_;
	std::shared_ptr<BezierCurve> left_curve_, right_curve_, top_curve_, bot_curve_;
	QVector4DMatrix coordinates_;
};


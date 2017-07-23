#pragma once
#include "model.hpp"
#include "clickable.hpp"
#include "beziercalculator.hpp"

class ControlGrid : public Model, public Clickable
{
public:
	ControlGrid(QVector4D start, QVector4DMatrix start_mat);
	~ControlGrid();
	void init(QVector4D* position = nullptr) override;
	void reinit(QVector4D* position = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void translateToReference() override;
	void setClicked(QVector4D& color) override;
	void setUnclicked(QVector4D& color) override;
	QVector4DMatrix getExtension() const;
private: 
	QVector4DMatrix coordinates_;
	QVector<QVector4D> distance_;
};


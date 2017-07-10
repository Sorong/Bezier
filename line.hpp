#pragma once
#include "model.hpp"

#ifndef LINES_H
#define LINES_H


class Line : public Model {
public:
	Line(QMatrix4x4& model, QVector4D position);
	void init(QVector4D* position = nullptr) override;
	void render(QMatrix4x4& projection, QMatrix4x4& view) override;
	void setCoordinates(QVector<QVector4D> &coordinates);
	void setColor(QVector4D color) override;
private:
};

#endif // LINES_H

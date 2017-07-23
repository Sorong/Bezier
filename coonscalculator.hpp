#pragma once
#include <QVector4D>
#include "beziercalculator.hpp"

class CoonsCalculator
{
public:
	CoonsCalculator();
	~CoonsCalculator();
	void getCoonsPatch(QVector4DMatrix& ltrb, QVector4DMatrix* patch, float precision_u, float precision_v);
};


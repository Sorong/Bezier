#pragma once
#include "model.hpp"
class BezierCurve :
	public Model
{
public:
	BezierCurve(QMatrix4x4 &model);
	~BezierCurve();
};


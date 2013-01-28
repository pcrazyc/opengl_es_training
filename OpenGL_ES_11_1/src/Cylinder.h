#pragma once

#include "Shape.h"
#include "MathUtil.h"

class Cylinder : public Shape {
public:
    Cylinder(float radius, float height);
	virtual void Reset();

private:
	float mRadius;
	float mHeight;
};
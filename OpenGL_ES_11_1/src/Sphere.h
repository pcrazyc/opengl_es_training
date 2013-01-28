#pragma once

#include "Shape.h"
#include "MathUtil.h"

class Sphere : public Shape {
public:
    Sphere(float radius);
	virtual void Reset();

private:
	float mRadius;
};
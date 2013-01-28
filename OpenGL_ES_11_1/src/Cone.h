#pragma once

#include "Shape.h"
#include "MathUtil.h"

class Cone : public Shape {
public:
    Cone(float radius, float height);
	virtual void Reset();

private:
	float mRadius;
	float mHeight;
};
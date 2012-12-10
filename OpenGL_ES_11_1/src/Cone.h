#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"

class Cone : public Shape {
public:
    Cone(float radius, float height);
    virtual void Draw();
	virtual void SetPos(float x=0, float y=0, float z=0);

private:
    float mBottomCircleVertexs[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];
    float mSideVertexs[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];

    float mColors[(CONE_CIRCLE_TRIANGLE_COUNT+2)*4];
};
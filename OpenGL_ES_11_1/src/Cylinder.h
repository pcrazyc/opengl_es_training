#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"

class Cylinder : public Shape {
public:
    Cylinder(float radius, float height);
    virtual void Draw();
	virtual void SetPos(float x=0, float y=0, float z=0);

private:
    float mBottomCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*3];
    float mTopCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*3];
    float mSideVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*6];

    float mBottomCircleColors[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*4];
    float mTopCircleColors[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*4];
    float mSideColors[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*8];
};
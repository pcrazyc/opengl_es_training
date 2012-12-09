#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"

class Cylinder : public Shape {
public:
    Cylinder(Vertex3D vecCenter, float radius, float height);
    virtual void draw();

private:
    float mBottomCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*3];
    float mTopCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*3];
    float mSideVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*6];

    float mBottomCircleColors[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*4];
    float mTopCircleColors[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*4];
    float mSideColors[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*8];
};
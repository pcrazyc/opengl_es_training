#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"

class Cone : public Shape {
public:
    Cone(Vertex3D vecCenter, float radius, float height);
    virtual void draw();

private:
    float mBottomCircleVertexs[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];
    float mSideVertexs[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];

    float mColors[(CONE_CIRCLE_TRIANGLE_COUNT+2)*4];
};
#pragma once

#include "Shape.h"
#include "MathUtil.h"

class Cylinder : public Shape {
public:
    Cylinder(Vertex3D vecCenter, float radius, float height);
    virtual void draw();

private:
    float *mBottomCircleVertexs;
    float *mTopCircleVertexs;
    float *mSideVertexs;
};
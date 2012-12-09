#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"

class Sphere : public Shape {
public:
    Sphere(Vertex3D vecCenter, float radius);
    virtual void draw();

private:
    float mVertexs[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*18];
    float mColors[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*24];
};
#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"

class Sphere : public Shape {
public:
    Sphere(float radius);
    virtual void Draw();
	virtual void SetPos(float x=0, float y=0, float z=0);

private:
    float mVertexs[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*18];
    float mColors[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*24];
};
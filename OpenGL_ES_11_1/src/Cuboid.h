#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"
#include "IwGL.h"

class Cuboid : public Shape {
public:
    Cuboid(float x, float y, float z);
    virtual void Draw();
	virtual void SetPos(float x=0, float y=0, float z=0);

private:
    float mVertexs[24];
    float mColors[24];
    const GLubyte *mIndices;
};
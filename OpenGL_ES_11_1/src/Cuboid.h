#pragma once

#include "Shape.h"
#include "MathUtil.h"
#include "Config.h"
#include "IwGL.h"

class Cuboid : public Shape {
public:
    Cuboid(Vertex3D &vecOrigin, Vertex3D &vecRitht, Vertex3D &vecTop, Vertex3D &vecFront);
    virtual void draw();

private:
    float mVertexs[24];
    float mColors[24];
    const GLubyte *mIndices;
};
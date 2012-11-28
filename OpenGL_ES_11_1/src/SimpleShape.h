#pragma once
#include "Shape.h"
#include "IwGL.h"

class SimpleShape : public Shape {
public:
    SimpleShape();
    SimpleShape(const float *vertices, const GLubyte *indices, const float *colors=NULL);
    virtual void draw();

public:
    const float *mVertices;
    const float *mColors;
    const GLubyte *mIndices;
};
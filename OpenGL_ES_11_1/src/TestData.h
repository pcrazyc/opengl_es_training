#ifndef _TEST_DATA_H
#define _TEST_DATA_H

#include "MathUtil.h"

float testTriangleVertexData[9] = {
    240.0f, 250.0f, -3.0f,
    50.0f, 70.0f, -3.0f,
    430.0f, 70.0f, -3.0f
};

float testTriangleColorData[12] = {
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f
};

#define PI 3.14159f


#define CYLINDER_CIRCLE_TRIANGLE_COUNT 5
Vertex3D cylinderCenter(0.0f, 0.0f, 0.0f);
float cylinderRadius = 1.0f;
float cylinderHeight = 2.0f;

#endif
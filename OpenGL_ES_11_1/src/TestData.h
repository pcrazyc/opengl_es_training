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

Vertex3D cylinderCenter(0.0f, 0.0f, 0.0f);
float cylinderRadius = 1.0f;
float cylinderHeight = 2.0f;

Vertex3D coneCenter(0.0f, 0.0f, 0.0f);
float coneRadius = 1.0f;
float coneHeight = 2.0f;

Vertex3D sphereCenter(0.0f, 0.0f, 0.0f);
float sphereRadius = 1.0f;

Vertex3D cubeOrigin(0.0f, 0.0f, 0.0f);
Vertex3D cubeRight(1.0f, 0.0f, 0.0f);
Vertex3D cubeTop(0.0f, 1.0f, 0.0f);
Vertex3D cubeFront(0.0f, 0.0f, 1.0f);

Vertex3D cuboidOrigin(0.0f, 0.0f, 0.0f);
Vertex3D cuboidRight(1.0f, 0.0f, 0.0f);
Vertex3D cuboidTop(0.0f, 2.0f, 0.0f);
Vertex3D cuboidFront(0.0f, 0.0f, 1.0f);

#endif
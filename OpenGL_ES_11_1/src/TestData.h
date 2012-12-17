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

float cylinderRadius = 1.0f;
float cylinderHeight = 2.0f;

float coneRadius = 1.0f;
float coneHeight = 2.0f;

float sphereRadius = 1.0f;

float cubeX = 1.0f;
float cubeY = 1.0f;
float cubeZ = 1.0f;

float cuboidX = 1.0f;
float cuboidY = 2.0f;
float cuboidZ = 1.0f;

float colorStepR = 0.21f;
float colorStepG = 0.13f;
float colorStepB = 0.05f;

#endif
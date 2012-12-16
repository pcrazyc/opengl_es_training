#include "Cuboid.h"
#include "math.h"

#include "stdio.h"
#include "TestColor.h"

Cuboid::Cuboid(float x, float y, float z) {
    DrawParam *drawCuboid = new DrawParam();
    drawList.push_back(drawCuboid);

    drawCuboid->drawType = DRAW_ELEMENTS;
    drawCuboid->mode = GL_TRIANGLES;
    drawCuboid->indicesType = GL_UNSIGNED_BYTE;
    drawCuboid->count = 36;

    drawCuboid->vertexPointer = new float[24];
    drawCuboid->colorPointer = new float[32];
    drawCuboid->normalPointer = new float[24];

    static const GLubyte indices[36] = {
        0, 1, 2, 0, 2, 3,
        1, 2, 5, 2, 5, 6,
        2, 3, 6, 3, 6, 7,
        4, 5, 6, 4, 6, 7,
        0, 1, 5, 0, 4, 5,
        0, 4, 7, 0, 3, 7
    };
    drawCuboid->indices = new GLubyte[36];
    for (int i=0; i<36; i++) {
        drawCuboid->indices[i] = indices[i];
    }

    TestColor::SharedTestColor()->InitColor();
    int vertexIndex = 0;
    int colorIndex = 0;
    int normalIndex = 0;

    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    drawCuboid->vertexPointer[vertexIndex++] = -0.5f*x;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*y;
    drawCuboid->vertexPointer[vertexIndex++] = 0.5f*z;
    TestColor::SharedTestColor()->GetNextColor(drawCuboid->colorPointer[colorIndex], drawCuboid->colorPointer[colorIndex+1], drawCuboid->colorPointer[colorIndex+2], drawCuboid->colorPointer[colorIndex+3]);
    colorIndex += 4;

    for (int i=0; i<8; i++) {
        float normalLenght = sqrtf(drawCuboid->vertexPointer[i*3]*drawCuboid->vertexPointer[i*3]
        +drawCuboid->vertexPointer[i*3+1]*drawCuboid->vertexPointer[i*3+1]
        +drawCuboid->vertexPointer[i*3+2]*drawCuboid->vertexPointer[i*3+2]);

        drawCuboid->normalPointer[i*3] = drawCuboid->vertexPointer[i*3]/normalLenght;
        drawCuboid->normalPointer[i*3+1] = drawCuboid->vertexPointer[i*3+1]/normalLenght;
        drawCuboid->normalPointer[i*3+2] = drawCuboid->vertexPointer[i*3+2]/normalLenght;
    }
}
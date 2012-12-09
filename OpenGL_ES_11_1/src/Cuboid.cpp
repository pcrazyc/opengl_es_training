#include "Cuboid.h"
#include "math.h"

#include "stdio.h"
#include "TestColor.h"

Cuboid::Cuboid(Vertex3D &vecOrigin, Vertex3D &vecRitht, Vertex3D &vecTop, Vertex3D &vecFront) {
    TestColor::SharedTestColor()->InitColor();
    int vertexIndex = 0;
    int colorIndex = 0;
    mVertexs[vertexIndex++] = vecOrigin.x;
    mVertexs[vertexIndex++] = vecOrigin.y;
    mVertexs[vertexIndex++] = vecOrigin.z;

    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = vecRitht.x;
    mVertexs[vertexIndex++] = vecRitht.y;
    mVertexs[vertexIndex++] = vecRitht.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[4], mColors[5], mColors[6]);
    mColors[7] = 1.0f;

    mVertexs[vertexIndex++] = vecRitht.x;
    mVertexs[vertexIndex++] = vecTop.y;
    mVertexs[vertexIndex++] = vecRitht.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = vecTop.x;
    mVertexs[vertexIndex++] = vecTop.y;
    mVertexs[vertexIndex++] = vecRitht.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = vecFront.x;
    mVertexs[vertexIndex++] = vecFront.y;
    mVertexs[vertexIndex++] = vecFront.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = vecRitht.x;
    mVertexs[vertexIndex++] = vecRitht.y;
    mVertexs[vertexIndex++] = vecFront.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = vecRitht.x;
    mVertexs[vertexIndex++] = vecTop.y;
    mVertexs[vertexIndex++] = vecFront.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = vecTop.x;
    mVertexs[vertexIndex++] = vecTop.y;
    mVertexs[vertexIndex++] = vecFront.z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    static const GLubyte indices[36] = {
        0, 1, 2, 0, 2, 3,
        1, 2, 5, 2, 5, 6,
        2, 3, 6, 3, 6, 7,
        4, 5, 6, 4, 6, 7,
        0, 1, 5, 0, 4, 5,
        0, 4, 7, 0, 3, 7
    };

    mIndices = indices;
}

void Cuboid::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mVertexs);
    glColorPointer(4, GL_FLOAT, 0, mColors);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, mIndices);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

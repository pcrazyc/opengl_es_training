#include "Cuboid.h"
#include "math.h"

#include "stdio.h"
#include "TestColor.h"

Cuboid::Cuboid(float x, float y, float z) {
    TestColor::SharedTestColor()->InitColor();
    int vertexIndex = 0;
    int colorIndex = 0;
    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = 0;

    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = x;
    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = 0;
    TestColor::SharedTestColor()->GetNextColor(mColors[4], mColors[5], mColors[6]);
    mColors[7] = 1.0f;

    mVertexs[vertexIndex++] = x;
    mVertexs[vertexIndex++] = y;
    mVertexs[vertexIndex++] = 0;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = y;
    mVertexs[vertexIndex++] = 0;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = x;
    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = x;
    mVertexs[vertexIndex++] = y;
    mVertexs[vertexIndex++] = z;
    TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
    colorIndex += 3;
    mColors[colorIndex++] = 1.0f;

    mVertexs[vertexIndex++] = 0;
    mVertexs[vertexIndex++] = y;
    mVertexs[vertexIndex++] = z;
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

void Cuboid::Draw() {
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

void Cuboid::SetPos( float x/*=0*/, float y/*=0*/, float z/*=0*/ ) {
	Shape::SetPos(x, y , z);

	for (int i=0; i<8; i++) {
		mVertexs[i*3] += mPosX;
		mVertexs[i*3+1] += mPosY;
		mVertexs[i*3+2] += mPosZ;
	}
}

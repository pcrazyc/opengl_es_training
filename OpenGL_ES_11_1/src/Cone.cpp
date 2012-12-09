#include "Cone.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Cone::Cone( Vertex3D vecCenter, float radius, float height ) {
    mBottomCircleVertexs[0] = vecCenter.x;
    mBottomCircleVertexs[1] = vecCenter.y;
    mBottomCircleVertexs[2] = vecCenter.z;

    mColors[0] = 0.0f;
    mColors[1] = 0.0f;
    mColors[2] = 0.0f;
    mColors[3] = 1.0f;

    mSideVertexs[0] = vecCenter.x;
    mSideVertexs[1] = vecCenter.y;
    mSideVertexs[2] = vecCenter.z + height;

    float angleStep = 2*PI/CONE_CIRCLE_TRIANGLE_COUNT;
    float angle = 0;

    int colorIndex = 0;
    for (int i=1; i<=CONE_CIRCLE_TRIANGLE_COUNT+1; i++, angle+=angleStep) {
        mBottomCircleVertexs[i*3] = vecCenter.x + radius * cosf(angle);
        mBottomCircleVertexs[i*3+1] = vecCenter.y + radius * sinf(angle);
        mBottomCircleVertexs[i*3+2] = vecCenter.z;

        TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
        colorIndex += 3;
        mColors[colorIndex++] = 1.0f;

        mSideVertexs[i*3] = vecCenter.x + radius * cosf(angle);
        mSideVertexs[i*3+1] = vecCenter.y + radius * sinf(angle);
        mSideVertexs[i*3+2] = vecCenter.z;
    }

    printf("angle: %f", angle);
}

void Cone::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mBottomCircleVertexs);
    glColorPointer(4, GL_FLOAT, 0, mColors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CONE_CIRCLE_TRIANGLE_COUNT+2);
    glPopMatrix();

    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mSideVertexs);
    glColorPointer(4, GL_FLOAT, 0, mColors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CONE_CIRCLE_TRIANGLE_COUNT+2);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


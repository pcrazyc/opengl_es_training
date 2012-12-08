#include "Cylinder.h"
#include "math.h"
#include "IwGL.h"
#include "TestData.h"

Cylinder::Cylinder( Vertex3D vecCenter, float radius, float height ) {
    mBottomCircleVertexs = new float[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*3];
    mTopCircleVertexs = new float[(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*3];
    mSideVertexs = new float [(CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*6];

    /*mBottomCircleVertexs[0] = vecCenter.x;
    mBottomCircleVertexs[1] = vecCenter.y;
    mBottomCircleVertexs[2] = vecCenter.z;

    mBottomCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*3] = vecCenter.x;
    mBottomCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*3+1] = vecCenter.y;
    mBottomCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*3+2] = vecCenter.z;


    mTopCircleVertexs[0] = vecCenter.x;
    mTopCircleVertexs[1] = vecCenter.y;
    mTopCircleVertexs[2] = vecCenter.z + height;

    mTopCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*3] = vecCenter.x;
    mTopCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*3+1] = vecCenter.y;
    mTopCircleVertexs[(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*3+2] = vecCenter.z + height;*/

    float angleStep = 2*PI/CYLINDER_CIRCLE_TRIANGLE_COUNT;
    float angle = 0;
    for (int i=0; i<=CYLINDER_CIRCLE_TRIANGLE_COUNT+1; i++, angle+=angleStep) {
        mBottomCircleVertexs[i*3] = radius * cosf(angle);
        mBottomCircleVertexs[i*3+1] = radius * sinf(angle);
        mBottomCircleVertexs[i*3+2] = vecCenter.z;

        mTopCircleVertexs[i*3] = radius * cosf(angle);
        mTopCircleVertexs[i*3+1] = radius * sinf(angle);
        mTopCircleVertexs[i*3+2] = vecCenter.z + height;
    }

    for (int i=0; i<=CYLINDER_CIRCLE_TRIANGLE_COUNT+1; i++) {
        mSideVertexs[i*6] = mBottomCircleVertexs[i*3];
        mSideVertexs[i*6+1] = mBottomCircleVertexs[i*3+1];
        mSideVertexs[i*6+2] = mBottomCircleVertexs[i*3+2];

        mSideVertexs[i*6+3] = mTopCircleVertexs[i*3];
        mSideVertexs[i*6+4] = mTopCircleVertexs[i*3+1];
        mSideVertexs[i*6+5] = mTopCircleVertexs[i*3+2];
    }

}

void Cylinder::draw() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mBottomCircleVertexs);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CYLINDER_CIRCLE_TRIANGLE_COUNT+2);
    glPopMatrix();

    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mTopCircleVertexs);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CYLINDER_CIRCLE_TRIANGLE_COUNT);
    glPopMatrix();

    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mSideVertexs);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (CYLINDER_CIRCLE_TRIANGLE_COUNT+2)*2);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
}
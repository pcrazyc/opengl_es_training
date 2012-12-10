#include "Cylinder.h"
#include "math.h"
#include "IwGL.h"
#include "TestData.h"
#include "stdio.h"
#include "TestColor.h"

Cylinder::Cylinder(float radius, float height ) {
    mBottomCircleVertexs[0] = 0;
    mBottomCircleVertexs[1] = 0;
    mBottomCircleVertexs[2] = 0;

    mBottomCircleColors[0] = 0.0f;
    mBottomCircleColors[1] = 0.0f;
    mBottomCircleColors[2] = 0.0f;
    mBottomCircleColors[3] = 1.0f;

    mTopCircleVertexs[0] = 0;
    mTopCircleVertexs[1] = 0;
    mTopCircleVertexs[2] = height;

    mTopCircleColors[0] = 0.0f;
    mTopCircleColors[1] = 0.0f;
    mTopCircleColors[2] = 0.0f;
    mTopCircleColors[3] = 1.0f;

    float angleStep = 2*PI/CYLINDER_CIRCLE_TRIANGLE_COUNT;
    float angle = 0;

    int colorBottomIndex = 0;
    int colorTopIndex = 0;
    TestColor::SharedTestColor()->InitColor();

    for (int i=1; i<=CYLINDER_CIRCLE_TRIANGLE_COUNT+1; i++, angle+=angleStep) {

        mBottomCircleVertexs[i*3] = radius * cosf(angle);
        mBottomCircleVertexs[i*3+1] = radius * sinf(angle);
        mBottomCircleVertexs[i*3+2] = 0;


        TestColor::SharedTestColor()->GetNextColor(mBottomCircleColors[colorBottomIndex], mBottomCircleColors[colorBottomIndex+1], mBottomCircleColors[colorBottomIndex+2]);
        colorBottomIndex += 3;
        mBottomCircleColors[colorBottomIndex++] = 1.0f;

        mTopCircleVertexs[i*3] = radius * cosf(angle);
        mTopCircleVertexs[i*3+1] = radius * sinf(angle);
        mTopCircleVertexs[i*3+2] = height;

        TestColor::SharedTestColor()->GetNextColor(mTopCircleColors[colorTopIndex], mTopCircleColors[colorTopIndex+1], mTopCircleColors[colorTopIndex+2]);
        colorTopIndex += 3;
        mTopCircleColors[colorTopIndex++] = 1.0f;
    }

    for (int i=0; i<=CYLINDER_CIRCLE_TRIANGLE_COUNT; i++) {
        mSideVertexs[i*6] = mBottomCircleVertexs[(i+1)*3];
        mSideVertexs[i*6+1] = mBottomCircleVertexs[(i+1)*3+1];
        mSideVertexs[i*6+2] = mBottomCircleVertexs[(i+1)*3+2];

        mSideVertexs[i*6+3] = mTopCircleVertexs[(i+1)*3];
        mSideVertexs[i*6+4] = mTopCircleVertexs[(i+1)*3+1];
        mSideVertexs[i*6+5] = mTopCircleVertexs[(i+1)*3+2];

        mSideColors[i*8] = mBottomCircleColors[(i+1)*4];
        mSideColors[i*8+1] = mBottomCircleColors[(i+1)*4+1];
        mSideColors[i*8+2] = mBottomCircleColors[(i+1)*4+2];
        mSideColors[i*8+3] = mBottomCircleColors[(i+1)*4+3];

        
        mSideColors[i*8+4] = mTopCircleColors[(i+1)*4];
        mSideColors[i*8+5] = mTopCircleColors[(i+1)*4+1];
        mSideColors[i*8+6] = mTopCircleColors[(i+1)*4+2];
        mSideColors[i*8+7] = mTopCircleColors[(i+1)*4+3];
    }
    printf("angle: %f", angle);
}

void Cylinder::Draw() {
	Shape::Draw();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mTopCircleVertexs);
    glColorPointer(4, GL_FLOAT, 0, mTopCircleColors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CYLINDER_CIRCLE_TRIANGLE_COUNT+2);

    glVertexPointer(3, GL_FLOAT, 0, mSideVertexs);
    glColorPointer(4, GL_FLOAT, 0, mSideColors);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*2);

    glVertexPointer(3, GL_FLOAT, 0, mBottomCircleVertexs);
    glColorPointer(4, GL_FLOAT, 0, mBottomCircleColors);
    glDrawArrays(GL_TRIANGLE_FAN, 0, CYLINDER_CIRCLE_TRIANGLE_COUNT+2);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}

void Cylinder::SetPos( float x/*=0*/, float y/*=0*/, float z/*=0*/ ) {
	Shape::SetPos(x, y , z);

	for (int i=0; i<CYLINDER_CIRCLE_TRIANGLE_COUNT+2; i++) {
		mBottomCircleVertexs[i*3] += mPosX;
		mBottomCircleVertexs[i*3+1] += mPosY;
		mBottomCircleVertexs[i*3+2] += mPosZ;

		mTopCircleVertexs[i*3] += mPosX;
		mTopCircleVertexs[i*3+1] += mPosY;
		mTopCircleVertexs[i*3+2] += mPosZ;
	}

	for (int i=0; i<(CYLINDER_CIRCLE_TRIANGLE_COUNT+1)*2; i++) {
		mSideVertexs[i*3] += mPosX;
		mSideVertexs[i*3+1] += mPosY;
		mSideVertexs[i*3+2] += mPosZ;
	}
}

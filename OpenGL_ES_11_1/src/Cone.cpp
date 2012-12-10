#include "Cone.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Cone::Cone( float radius, float height ) {
    mBottomCircleVertexs[0] = 0;
    mBottomCircleVertexs[1] = 0;
    mBottomCircleVertexs[2] = 0;

    mColors[0] = 0.0f;
    mColors[1] = 0.0f;
    mColors[2] = 0.0f;
    mColors[3] = 1.0f;

    mSideVertexs[0] = 0;
    mSideVertexs[1] = 0;
    mSideVertexs[2] = height;

    float angleStep = 2*PI/CONE_CIRCLE_TRIANGLE_COUNT;
    float angle = 0;

    int colorIndex = 0;
    for (int i=1; i<=CONE_CIRCLE_TRIANGLE_COUNT+1; i++, angle+=angleStep) {
        mBottomCircleVertexs[i*3] = radius * cosf(angle);
        mBottomCircleVertexs[i*3+1] = radius * sinf(angle);
        mBottomCircleVertexs[i*3+2] = 0;

        TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
        colorIndex += 3;
        mColors[colorIndex++] = 1.0f;

        mSideVertexs[i*3] = radius * cosf(angle);
        mSideVertexs[i*3+1] = radius * sinf(angle);
        mSideVertexs[i*3+2] = 0;
    }

    printf("angle: %f", angle);
}

void Cone::Draw() {
	Shape::Draw();

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

void Cone::SetPos( float x/*=0*/, float y/*=0*/, float z/*=0*/ ) {
	Shape::SetPos(x, y , z);

	for (int i=0; i<CONE_CIRCLE_TRIANGLE_COUNT+2; i++) {
		mBottomCircleVertexs[i*3] += mPosX;
		mBottomCircleVertexs[i*3+1] += mPosY;
		mBottomCircleVertexs[i*3+2] += mPosZ;

		mSideVertexs[i*3] += mPosX;
		mSideVertexs[i*3+1] += mPosY;
		mSideVertexs[i*3+2] += mPosZ;
	}
}


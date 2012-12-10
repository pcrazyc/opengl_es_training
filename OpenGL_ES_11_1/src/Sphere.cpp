#include "Sphere.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Sphere::Sphere( float radius ) {
    float angleLatitude = -1*0.5f*PI;
    float angleLongitude = 0.0f;

    float angleLatitudeStep = PI/SPHERE_LATITUDE_COUNT;
    float angleLongitudeStep = 2*PI/SPHERE_LONGITUDE_COUNT;

    int vertexIndex = 0;
    int colorIndex = 0;

    for (int i=0; i<(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*18; i++) {
        mVertexs[i] = 0;
    }
    for (int i=0; i<=SPHERE_LATITUDE_COUNT; i++, angleLatitude+=angleLatitudeStep) {
        for (int j=0; j<=SPHERE_LONGITUDE_COUNT; j++, angleLongitude+=angleLongitudeStep) {
            TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
            colorIndex += 3;
            mColors[colorIndex++] = 1.0f;

            mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude+angleLongitudeStep);
            mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude+angleLongitudeStep);
            mVertexs[vertexIndex++] = radius*sinf(angleLatitude);


            TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
            colorIndex += 3;
            mColors[colorIndex++] = 1.0f;

            mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
            mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
            mVertexs[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

            TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
            colorIndex += 3;
            mColors[colorIndex++] = 1.0f;

            mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude);
            mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude);
            mVertexs[vertexIndex++] = radius*sinf(angleLatitude);

            mColors[colorIndex++] = mColors[colorIndex-12];
            mColors[colorIndex++] = mColors[colorIndex-12];
            mColors[colorIndex++] = mColors[colorIndex-12];
            mColors[colorIndex++] = mColors[colorIndex-12];

            mVertexs[vertexIndex++] = mVertexs[vertexIndex-9];
            mVertexs[vertexIndex++] = mVertexs[vertexIndex-9];
            mVertexs[vertexIndex++] = mVertexs[vertexIndex-9];

            mColors[colorIndex++] = mColors[colorIndex-12];
            mColors[colorIndex++] = mColors[colorIndex-12];
            mColors[colorIndex++] = mColors[colorIndex-12];
            mColors[colorIndex++] = mColors[colorIndex-12];

            mVertexs[vertexIndex++] = mVertexs[vertexIndex-9];
            mVertexs[vertexIndex++] = mVertexs[vertexIndex-9];
            mVertexs[vertexIndex++] = mVertexs[vertexIndex-9];


            TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
            colorIndex += 3;
            mColors[colorIndex++] = 1.0f;

            mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude);
            mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude);
            mVertexs[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);
        }
    }

    for (int i=0; i<vertexIndex; i++) {
        if (mVertexs[i]<-1 || mVertexs[i]>1) {
            printf("test");
        }
    }
    printf("test");
}

void Sphere::Draw() {
	Shape::Draw();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glPushMatrix();
    glVertexPointer(3, GL_FLOAT, 0, mVertexs);
    glColorPointer(4, GL_FLOAT, 0, mColors);
    glDrawArrays(GL_TRIANGLES, 0, (SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*6);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void Sphere::SetPos( float x/*=0*/, float y/*=0*/, float z/*=0*/ ) {
	Shape::SetPos(x, y , z);

	for (int i=0; i<(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*6; i++) {
		mVertexs[i*3] += mPosX;
		mVertexs[i*3+1] += mPosY;
		mVertexs[i*3+2] += mPosZ;
	}
}



/*#include "Sphere.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Sphere::Sphere( float radius ) {
float angleLatitude = -1*0.5f*PI;
float angleLongitude = 0.0f;

float angleLatitudeStep = PI/SPHERE_LATITUDE_COUNT;
float angleLongitudeStep = 2*PI/SPHERE_LONGITUDE_COUNT;

int vertexIndex = 0;
int colorIndex = 0;
for (int i=0; i<SPHERE_LATITUDE_COUNT; i++, angleLatitude+=angleLatitudeStep) {
for (int j=0; j<SPHERE_LONGITUDE_COUNT; j++, angleLongitude+=angleLongitudeStep) {
TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
colorIndex += 3;
mColors[colorIndex++] = 1.0f;

mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude);
mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude);
mVertexs[vertexIndex++] = radius*sinf(angleLatitude);

TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
colorIndex += 3;
mColors[colorIndex++] = 1.0f;

mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude);
mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude);
mVertexs[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
colorIndex += 3;
mColors[colorIndex++] = 1.0f;

mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
mVertexs[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
mVertexs[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

TestColor::SharedTestColor()->GetNextColor(mColors[colorIndex], mColors[colorIndex+1], mColors[colorIndex+2]);
colorIndex += 3;
mColors[colorIndex++] = 1.0f;

mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude+angleLongitudeStep);
mVertexs[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude+angleLongitudeStep);
mVertexs[vertexIndex++] = radius*sinf(angleLatitude);
}
}
}

void Sphere::draw() {
glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);

glPushMatrix();
glVertexPointer(3, GL_FLOAT, 0, mVertexs);
glColorPointer(4, GL_FLOAT, 0, mColors);
glDrawArrays(GL_TRIANGLE_FAN, 0, SPHERE_LATITUDE_COUNT*SPHERE_LONGITUDE_COUNT*4);
glPopMatrix();

glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_COLOR_ARRAY);
}

*/
#include "Sphere.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Sphere::Sphere( float radius ) {
    DrawParam *drawSphere = new DrawParam();
    drawList.push_back(drawSphere);

    drawSphere->vertexPointer = new float[(SPHERE_LATITUDE_COUNT+2)*(SPHERE_LONGITUDE_COUNT+2)*18];
    drawSphere->colorPointer = new float[(SPHERE_LATITUDE_COUNT+2)*(SPHERE_LONGITUDE_COUNT+2)*24];
    drawSphere->normalPointer = new float[(SPHERE_LATITUDE_COUNT+2)*(SPHERE_LONGITUDE_COUNT+2)*18];
    drawSphere->drawType = DRAW_ARRAYS;
    drawSphere->mode = GL_TRIANGLES;
    drawSphere->first = 0;
    drawSphere->count = (SPHERE_LATITUDE_COUNT+2)*(SPHERE_LONGITUDE_COUNT+2)*6;

    float angleLatitude = -1*0.5f*PI;
    float angleLongitude = 0.0f;

    float angleLatitudeStep = PI/SPHERE_LATITUDE_COUNT;
    float angleLongitudeStep = 2*PI/SPHERE_LONGITUDE_COUNT;

    int vertexIndex = 0;
    int colorIndex = 0;

    for (int i=0; i<=SPHERE_LATITUDE_COUNT+1; i++, angleLatitude+=angleLatitudeStep) {
        for (int j=0; j<=SPHERE_LONGITUDE_COUNT+1; j++, angleLongitude+=angleLongitudeStep) {
            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude);

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude);

			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];
			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];
			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];
			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];

			drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-6];
			drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-6];
			drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-6];

			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];
			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];
			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];
			drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-8];

			drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-6];
			drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-6];
			drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-6];
			
			/*TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
			colorIndex += 4;

			drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
			drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
			drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

			TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
			colorIndex += 4;

			drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude);*/

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

			drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);
        }
    }

	for (int i=0; i<vertexIndex; i++) {
		drawSphere->normalPointer[i] = drawSphere->vertexPointer[i];
	}
}
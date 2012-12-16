#include "Sphere.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Sphere::Sphere( float radius ) {
    DrawParam *drawSphere = new DrawParam();
    drawList.push_back(drawSphere);

    drawSphere->vertexPointer = new float[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*18];
    drawSphere->colorPointer = new float[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*24];
    drawSphere->normalPointer = new float[(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*18];
    drawSphere->drawType = DRAW_ARRAYS;
    drawSphere->mode = GL_TRIANGLES;
    drawSphere->first = 0;
    drawSphere->count = (SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*6;

    float angleLatitude = -1*0.5f*PI;
    float angleLongitude = 0.0f;

    float angleLatitudeStep = PI/SPHERE_LATITUDE_COUNT;
    float angleLongitudeStep = 2*PI/SPHERE_LONGITUDE_COUNT;

    int vertexIndex = 0;
    int normalIndex = 0;
    int colorIndex = 0;

    for (int i=0; i<(SPHERE_LATITUDE_COUNT+1)*(SPHERE_LONGITUDE_COUNT+1)*18; i++) {
        drawSphere->vertexPointer[i] = 0;
    }
    for (int i=0; i<=SPHERE_LATITUDE_COUNT; i++, angleLatitude+=angleLatitudeStep) {
        for (int j=0; j<=SPHERE_LONGITUDE_COUNT; j++, angleLongitude+=angleLongitudeStep) {
            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude);

            drawSphere->normalPointer[normalIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->normalPointer[normalIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->normalPointer[normalIndex++] = radius*sinf(angleLatitude);

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

            drawSphere->normalPointer[normalIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->normalPointer[normalIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->normalPointer[normalIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude);

            drawSphere->normalPointer[normalIndex++] = radius*cosf(angleLatitude)*cosf(angleLongitude);
            drawSphere->normalPointer[normalIndex++] = radius*cosf(angleLatitude)*sinf(angleLongitude);
            drawSphere->normalPointer[normalIndex++] = radius*sinf(angleLatitude);

            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];
            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];
            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];
            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];

            drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-9];
            drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-9];
            drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-9];

            drawSphere->normalPointer[normalIndex++] = drawSphere->normalPointer[normalIndex-9];
            drawSphere->normalPointer[normalIndex++] = drawSphere->normalPointer[normalIndex-9];
            drawSphere->normalPointer[normalIndex++] = drawSphere->normalPointer[normalIndex-9];

            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];
            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];
            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];
            drawSphere->colorPointer[colorIndex++] = drawSphere->colorPointer[colorIndex-12];

            drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-9];
            drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-9];
            drawSphere->vertexPointer[vertexIndex++] = drawSphere->vertexPointer[vertexIndex-9];

            drawSphere->normalPointer[normalIndex++] = drawSphere->normalPointer[normalIndex-9];
            drawSphere->normalPointer[normalIndex++] = drawSphere->normalPointer[normalIndex-9];
            drawSphere->normalPointer[normalIndex++] = drawSphere->normalPointer[normalIndex-9];


            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = radius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = radius*sinf(angleLatitude+angleLatitudeStep);
        }
    }

    for (int i=0; i<vertexIndex; i++) {
        if (drawSphere->vertexPointer[i]<-1 || drawSphere->vertexPointer[i]>1) {
            printf("test");
        }
    }
    printf("test");
}
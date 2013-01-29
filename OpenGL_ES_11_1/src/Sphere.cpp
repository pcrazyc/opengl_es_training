#include "Sphere.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"
#include "ConfigManager.h"


void texcoord(float& v0,float& v1, float& v2, float &x, float &y)  
{
	y =(float)( 1 - acos((double)v2)/PI);
	double temp = sqrt(v0*v0 + v1*v1);
	x = (float)acos((double)v0/temp);
	if(v1 < 0)
		x = 2*PI - x;
	x /= (2*PI);

	y = y * -1.0f + 1.0f;
}
Sphere::Sphere( float radius ) {
    mRadius = radius;

	Reset();
}

void Sphere::Reset() {
	Clean();

	DrawParam *drawSphere = new DrawParam();
    drawList.push_back(drawSphere);

	int sphere_latitude_count = ConfigManager::SharedConfigManager()->GetConfigData(SphereLatitudeCount);
	int sphere_longitude_count = ConfigManager::SharedConfigManager()->GetConfigData(SphereLongitudeCount);

    drawSphere->vertexPointer = new float[(sphere_latitude_count+2)*(sphere_longitude_count+2)*18];
    drawSphere->colorPointer = new float[(sphere_latitude_count+2)*(sphere_longitude_count+2)*24];
    drawSphere->normalPointer = new float[(sphere_latitude_count+2)*(sphere_longitude_count+2)*18];
	drawSphere->texturePointer = new float[(sphere_latitude_count+2)*(sphere_longitude_count+2)*12];//u,v

    drawSphere->drawType = DRAW_ARRAYS;
    drawSphere->mode = GL_TRIANGLES;
    drawSphere->first = 0;
    drawSphere->count = (sphere_latitude_count+2)*(sphere_longitude_count+2)*6;

    float angleLatitude = -1*0.5f*PI;
    float angleLongitude = 0.0f;

    float angleLatitudeStep = PI/sphere_latitude_count;
    float angleLongitudeStep = 2*PI/sphere_longitude_count;

    int vertexIndex = 0;
    int colorIndex = 0;

    for (int i=0; i<=sphere_latitude_count+1; i++, angleLatitude+=angleLatitudeStep) {
        for (int j=0; j<=sphere_longitude_count+1; j++, angleLongitude+=angleLongitudeStep) {
            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = mRadius*sinf(angleLatitude);

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
            drawSphere->vertexPointer[vertexIndex++] = mRadius*sinf(angleLatitude+angleLatitudeStep);

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

            drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude)*cosf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude)*sinf(angleLongitude);
            drawSphere->vertexPointer[vertexIndex++] = mRadius*sinf(angleLatitude);

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

			drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude+angleLongitudeStep);
			drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude+angleLongitudeStep);
			drawSphere->vertexPointer[vertexIndex++] = mRadius*sinf(angleLatitude+angleLatitudeStep);

			TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
			colorIndex += 4;

			drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude)*cosf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude)*sinf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = mRadius*sinf(angleLatitude);*/

            TestColor::SharedTestColor()->GetNextColor(drawSphere->colorPointer[colorIndex], drawSphere->colorPointer[colorIndex+1], drawSphere->colorPointer[colorIndex+2], drawSphere->colorPointer[colorIndex+3]);
            colorIndex += 4;

			drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude+angleLatitudeStep)*cosf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = mRadius*cosf(angleLatitude+angleLatitudeStep)*sinf(angleLongitude);
			drawSphere->vertexPointer[vertexIndex++] = mRadius*sinf(angleLatitude+angleLatitudeStep);
        }
    }

	for (int i=0; i<vertexIndex; i++) {
		drawSphere->normalPointer[i] = drawSphere->vertexPointer[i];
	}

	//(-1,1)  to (0,1)
	//x,y to u,v
	int aCount = (sphere_latitude_count+2)*(sphere_longitude_count+2) * 6;
	for (int i =0 ; i < aCount; i++)
	{
		texcoord(drawSphere->vertexPointer[3 * i +2],drawSphere->vertexPointer[3 * i +0],drawSphere->vertexPointer[3 * i +1],
			drawSphere->texturePointer[2 * i], drawSphere->texturePointer[2 * i+1]);
	}
    //for (int i=0; i<vertexIndex; i++) {
    //    if (drawSphere->vertexPointer[i]<0) {
    //        printf("**************test");
    //    }
    //}
	SetTexture("Images/earth.bmp");
}

#include "Cone.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"
#include "ConfigManager.h"

Cone::Cone( float radius, float height ) {
	mRadius = radius;
	mHeight = height;

	Reset();
}

void Cone::Reset() {
	Clean();

	DrawParam *drawBottom = new DrawParam();
	DrawParam *drawSide = new DrawParam();
	drawList.push_back(drawBottom);
	drawList.push_back(drawSide);

	int cone_circle_triangle_count = ConfigManager::SharedConfigManager()->GetConfigData(ConeCircleTriangleCount);

	drawBottom->vertexPointer = new float[(cone_circle_triangle_count+2)*3];
	drawBottom->colorPointer = new float[(cone_circle_triangle_count+2)*4];
	drawBottom->normalPointer = new float[(cone_circle_triangle_count+2)*3];
	drawBottom->drawType = DRAW_ARRAYS;
	drawBottom->mode = GL_TRIANGLE_FAN;
	drawBottom->first = 0;
	drawBottom->count = cone_circle_triangle_count+2;

	drawSide->vertexPointer = new float[(cone_circle_triangle_count+2)*3];
	drawSide->colorPointer = new float[(cone_circle_triangle_count+2)*4];
	drawSide->normalPointer = new float[(cone_circle_triangle_count+2)*3];
	drawSide->drawType = DRAW_ARRAYS;
	drawSide->mode = GL_TRIANGLE_FAN;
	drawSide->first = 0;
	drawSide->count = cone_circle_triangle_count+2;

	TestColor::SharedTestColor()->InitColor();
	int colorIndex = 0;

	drawBottom->vertexPointer[0] = 0;
	drawBottom->vertexPointer[1] = -0.5f*mHeight;
	drawBottom->vertexPointer[2] = 0;
	drawBottom->normalPointer[0] = 0;
	drawBottom->normalPointer[1] = -1.0f;
	drawBottom->normalPointer[2] = 0;
	TestColor::SharedTestColor()->GetNextColor(drawBottom->colorPointer[colorIndex], drawBottom->colorPointer[colorIndex+1], drawBottom->colorPointer[colorIndex+2], drawBottom->colorPointer[colorIndex+3]);
	colorIndex += 4;

	drawSide->vertexPointer[0] = 0;
	drawSide->vertexPointer[1] = 0.5f*mHeight;
	drawSide->vertexPointer[2] = 0;
	drawSide->normalPointer[0] = 0;
	drawSide->normalPointer[1] = 1.0f;
	drawSide->normalPointer[2] = 0;

	TestColor::SharedTestColor()->GetNextColor(drawSide->colorPointer[0], drawSide->colorPointer[1], drawSide->colorPointer[2], drawSide->colorPointer[3]);

	float angleStep = 2*PI/cone_circle_triangle_count;
	float angle = 0;

	for (int i=1; i<cone_circle_triangle_count+2; i++, angle+=angleStep) {
		drawBottom->vertexPointer[i*3] = mRadius * cosf(angle);
		drawBottom->vertexPointer[i*3+1] = -0.5f*mHeight;
		drawBottom->vertexPointer[i*3+2] = mRadius * sinf(angle);

		TestColor::SharedTestColor()->GetNextColor(drawBottom->colorPointer[colorIndex], drawBottom->colorPointer[colorIndex+1], drawBottom->colorPointer[colorIndex+2], drawBottom->colorPointer[colorIndex+3]);
		colorIndex += 4;

		drawSide->vertexPointer[i*3] = mRadius * cosf(angle);
		drawSide->vertexPointer[i*3+1] = -0.5f*mHeight;
		drawSide->vertexPointer[i*3+2] = mRadius * sinf(angle);
	}

	for (int i=1; i<cone_circle_triangle_count+2; i++) {
		float normalLenght = sqrtf(drawBottom->vertexPointer[i*3]*drawBottom->vertexPointer[i*3]
		+drawBottom->vertexPointer[i*3+1]*drawBottom->vertexPointer[i*3+1]
		+drawBottom->vertexPointer[i*3+2]*drawBottom->vertexPointer[i*3+2]);

		drawBottom->normalPointer[i*3] = drawBottom->vertexPointer[i*3]/normalLenght;
		drawBottom->normalPointer[i*3+1] = drawBottom->vertexPointer[i*3+1]/normalLenght;
		drawBottom->normalPointer[i*3+2] = drawBottom->vertexPointer[i*3+2]/normalLenght;

		drawSide->normalPointer[i*3] = drawBottom->normalPointer[i*3];
		drawSide->normalPointer[i*3+1] = drawBottom->normalPointer[i*3+1];
		drawSide->normalPointer[i*3+2] = drawBottom->normalPointer[i*3+2];
	}

	for (int i=4; i<colorIndex; i++) {
		drawSide->colorPointer[i] =drawBottom->colorPointer[i];
	}

	printf("angle: %f", angle);
}

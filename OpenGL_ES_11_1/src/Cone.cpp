#include "Cone.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"

Cone::Cone( float radius, float height ) {
	DrawParam *drawBottom = new DrawParam();
	DrawParam *drawSide = new DrawParam();
	drawList.push_back(drawBottom);
	drawList.push_back(drawSide);

	drawBottom->vertexPointer = new float[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];
	drawBottom->colorPointer = new float[(CONE_CIRCLE_TRIANGLE_COUNT+2)*4];
	drawBottom->normalPointer = new float[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];
	drawBottom->drawType = DRAW_ARRAYS;
	drawBottom->mode = GL_TRIANGLE_FAN;
	drawBottom->first = 0;
	drawBottom->count = CONE_CIRCLE_TRIANGLE_COUNT+2;

	drawSide->vertexPointer = new float[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];
	drawSide->colorPointer = new float[(CONE_CIRCLE_TRIANGLE_COUNT+2)*4];
	drawSide->normalPointer = new float[(CONE_CIRCLE_TRIANGLE_COUNT+2)*3];
	drawSide->drawType = DRAW_ARRAYS;
	drawSide->mode = GL_TRIANGLE_FAN;
	drawSide->first = 0;
	drawSide->count = CONE_CIRCLE_TRIANGLE_COUNT+2;

	TestColor::SharedTestColor()->InitColor();
	int colorIndex = 0;

	drawBottom->vertexPointer[0] = 0;
	drawBottom->vertexPointer[1] = -0.5f*height;
	drawBottom->vertexPointer[2] = 0;
	drawBottom->normalPointer[0] = 0;
	drawBottom->normalPointer[1] = -1.0f;
	drawBottom->normalPointer[2] = 0;
	TestColor::SharedTestColor()->GetNextColor(drawBottom->colorPointer[colorIndex], drawBottom->colorPointer[colorIndex+1], drawBottom->colorPointer[colorIndex+2], drawBottom->colorPointer[colorIndex+3]);
	colorIndex += 4;

	drawSide->vertexPointer[0] = 0;
	drawSide->vertexPointer[1] = 0.5f*height;
	drawSide->vertexPointer[2] = 0;
	drawSide->normalPointer[0] = 0;
	drawSide->normalPointer[1] = 1.0f;
	drawSide->normalPointer[2] = 0;

	TestColor::SharedTestColor()->GetNextColor(drawSide->colorPointer[0], drawSide->colorPointer[1], drawSide->colorPointer[2], drawSide->colorPointer[3]);

	float angleStep = 2*PI/CONE_CIRCLE_TRIANGLE_COUNT;
	float angle = 0;

	for (int i=1; i<CONE_CIRCLE_TRIANGLE_COUNT+2; i++, angle+=angleStep) {
		drawBottom->vertexPointer[i*3] = radius * cosf(angle);
		drawBottom->vertexPointer[i*3+1] = -0.5f*height;
		drawBottom->vertexPointer[i*3+2] = radius * sinf(angle);

		TestColor::SharedTestColor()->GetNextColor(drawBottom->colorPointer[colorIndex], drawBottom->colorPointer[colorIndex+1], drawBottom->colorPointer[colorIndex+2], drawBottom->colorPointer[colorIndex+3]);
		colorIndex += 4;

		drawSide->vertexPointer[i*3] = radius * cosf(angle);
		drawSide->vertexPointer[i*3+1] = -0.5f*height;
		drawSide->vertexPointer[i*3+2] = radius * sinf(angle);
	}

	for (int i=1; i<CONE_CIRCLE_TRIANGLE_COUNT+2; i++) {
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
#include "Cylinder.h"
#include "math.h"
#include "IwGL.h"
#include "stdio.h"
#include "TestColor.h"
#include "ConfigManager.h"

Cylinder::Cylinder(float radius, float height ) {
	mRadius = radius;
	mHeight = height;

    Reset();
}

void Cylinder::Reset() {
	Clean();

	DrawParam *drawBottom = new DrawParam();
	DrawParam *drawTop = new DrawParam();
	DrawParam *drawSide = new DrawParam();

	drawList.push_back(drawBottom);
	drawList.push_back(drawSide);
	drawList.push_back(drawTop);

	int cylinder_circle_triangle_count = atoi(ConfigManager::SharedConfigManager()->GetConfigData(CylinderCircleTriangleCount));

	drawBottom->vertexPointer = new float[(cylinder_circle_triangle_count+2)*3];
	drawBottom->colorPointer = new float[(cylinder_circle_triangle_count+2)*4];
	drawBottom->normalPointer = new float[(cylinder_circle_triangle_count+2)*3];
	drawBottom->drawType = DRAW_ARRAYS;
	drawBottom->mode = GL_TRIANGLE_FAN;
	drawBottom->first = 0;
	drawBottom->count = cylinder_circle_triangle_count+2;

	drawSide->vertexPointer = new float[(cylinder_circle_triangle_count+1)*6];
	drawSide->colorPointer = new float[(cylinder_circle_triangle_count+1)*8];
	drawSide->normalPointer = new float[(cylinder_circle_triangle_count+1)*6];
	drawSide->drawType = DRAW_ARRAYS;
	drawSide->mode = GL_TRIANGLE_STRIP;
	drawSide->first = 0;
	drawSide->count = (cylinder_circle_triangle_count+1)*2;

	drawTop->vertexPointer = new float[(cylinder_circle_triangle_count+2)*3];
	drawTop->colorPointer = new float[(cylinder_circle_triangle_count+2)*4];
	drawTop->normalPointer = new float[(cylinder_circle_triangle_count+2)*3];
	drawTop->drawType = DRAW_ARRAYS;
	drawTop->mode = GL_TRIANGLE_FAN;
	drawTop->first = 0;
	drawTop->count = cylinder_circle_triangle_count+2;

	drawBottom->vertexPointer[0] = 0;
	drawBottom->vertexPointer[1] = -0.5f*mHeight;
	drawBottom->vertexPointer[2] = 0;

	drawBottom->normalPointer[0] = 0;
	drawBottom->normalPointer[1] = -1.0f;
	drawBottom->normalPointer[2] = 0;

	drawBottom->colorPointer[0] = 0.0f;
	drawBottom->colorPointer[1] = 0.0f;
	drawBottom->colorPointer[2] = 0.0f;
	drawBottom->colorPointer[3] = 1.0f;


	drawTop->vertexPointer[0] = 0;
	drawTop->vertexPointer[1] = 0.5f*mHeight;
	drawTop->vertexPointer[2] = 0;

	drawTop->normalPointer[0] = 0;
	drawTop->normalPointer[1] = 1.0f;
	drawTop->normalPointer[2] = 0;

	drawTop->colorPointer[0] = 0.0f;
	drawTop->colorPointer[1] = 0.0f;
	drawTop->colorPointer[2] = 0.0f;
	drawTop->colorPointer[3] = 1.0f;

	float angleStep = 2*PI/cylinder_circle_triangle_count;
	float angle = 0;

	int colorBottomIndex = 0;
	int colorTopIndex = 0;
	TestColor::SharedTestColor()->InitColor();

	for (int i=1; i<cylinder_circle_triangle_count+2; i++, angle+=angleStep) {
		drawBottom->vertexPointer[i*3] = mRadius * cosf(angle);
		drawBottom->vertexPointer[i*3+1] = -0.5f*mHeight;
		drawBottom->vertexPointer[i*3+2] = mRadius * sinf(angle);

		TestColor::SharedTestColor()->GetNextColor(drawBottom->colorPointer[colorBottomIndex], drawBottom->colorPointer[colorBottomIndex+1], drawBottom->colorPointer[colorBottomIndex+2], drawBottom->colorPointer[colorBottomIndex+3]);
		colorBottomIndex += 4;


		drawTop->vertexPointer[i*3] = mRadius * cosf(angle);
		drawTop->vertexPointer[i*3+1] = 0.5f*mHeight;
		drawTop->vertexPointer[i*3+2] = mRadius * sinf(angle);

		TestColor::SharedTestColor()->GetNextColor(drawTop->colorPointer[colorTopIndex], drawTop->colorPointer[colorTopIndex+1], drawTop->colorPointer[colorTopIndex+2], drawTop->colorPointer[colorTopIndex+3]);
		colorTopIndex += 4;
	}

	for (int i=1; i<cylinder_circle_triangle_count+2; i++) {
		float normalLenght = sqrtf(drawBottom->vertexPointer[i*3]*drawBottom->vertexPointer[i*3]
		+drawBottom->vertexPointer[i*3+1]*drawBottom->vertexPointer[i*3+1]
		+drawBottom->vertexPointer[i*3+2]*drawBottom->vertexPointer[i*3+2]);
		drawBottom->normalPointer[i*3] = drawBottom->vertexPointer[i*3]/normalLenght;
		drawBottom->normalPointer[i*3+1] = drawBottom->vertexPointer[i*3+1]/normalLenght;
		drawBottom->normalPointer[i*3+2] = drawBottom->vertexPointer[i*3+2]/normalLenght;

		normalLenght = sqrtf(drawTop->vertexPointer[i*3]*drawTop->vertexPointer[i*3]
		+drawTop->vertexPointer[i*3+1]*drawTop->vertexPointer[i*3+1]
		+drawTop->vertexPointer[i*3+2]*drawTop->vertexPointer[i*3+2]);
		drawTop->normalPointer[i*3] = drawTop->vertexPointer[i*3]/normalLenght;
		drawTop->normalPointer[i*3+1] = drawTop->vertexPointer[i*3+1]/normalLenght;
		drawTop->normalPointer[i*3+2] = drawTop->vertexPointer[i*3+2]/normalLenght;
	}

	for (int i=0; i<=cylinder_circle_triangle_count; i++) {
		drawSide->vertexPointer[i*6] = drawBottom->vertexPointer[(i+1)*3];
		drawSide->vertexPointer[i*6+1] = drawBottom->vertexPointer[(i+1)*3+1];
		drawSide->vertexPointer[i*6+2] = drawBottom->vertexPointer[(i+1)*3+2];

		drawSide->vertexPointer[i*6+3] = drawTop->vertexPointer[(i+1)*3];
		drawSide->vertexPointer[i*6+4] = drawTop->vertexPointer[(i+1)*3+1];
		drawSide->vertexPointer[i*6+5] = drawTop->vertexPointer[(i+1)*3+2];

		drawSide->normalPointer[i*6] = drawBottom->normalPointer[(i+1)*3];
		drawSide->normalPointer[i*6+1] = drawBottom->normalPointer[(i+1)*3+1];
		drawSide->normalPointer[i*6+2] = drawBottom->normalPointer[(i+1)*3+2];

		drawSide->normalPointer[i*6+3] = drawTop->normalPointer[(i+1)*3];
		drawSide->normalPointer[i*6+4] = drawTop->normalPointer[(i+1)*3+1];
		drawSide->normalPointer[i*6+5] = drawTop->normalPointer[(i+1)*3+2];

		drawSide->colorPointer[i*8] = drawBottom->colorPointer[(i+1)*4];
		drawSide->colorPointer[i*8+1] = drawBottom->colorPointer[(i+1)*4+1];
		drawSide->colorPointer[i*8+2] = drawBottom->colorPointer[(i+1)*4+2];
		drawSide->colorPointer[i*8+3] = drawBottom->colorPointer[(i+1)*4+3];

		drawSide->colorPointer[i*8+4] = drawTop->colorPointer[(i+1)*4];
		drawSide->colorPointer[i*8+5] = drawTop->colorPointer[(i+1)*4+1];
		drawSide->colorPointer[i*8+6] = drawTop->colorPointer[(i+1)*4+2];
		drawSide->colorPointer[i*8+7] = drawTop->colorPointer[(i+1)*4+3];
	}

	printf("angle: %f", angle);
}

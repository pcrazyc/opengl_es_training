#pragma once

#include "IwGL.h"

class Shape {
public:
	virtual void Update() {
		glMatrixMode(GL_MODELVIEW);
		glRotatef(0.3f, 0.0f, 0.0f, 1.0f);
	}
    virtual void Draw() {
		/*glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(mPosX, mPosY, mPosZ);*/
	}
	virtual void SetPos(float x=0, float y=0, float z=0) {
		mPosX = x;
		mPosY = y;
		mPosZ = z;
	}

public:
	float mPosX;
	float mPosY;
	float mPosZ;
};
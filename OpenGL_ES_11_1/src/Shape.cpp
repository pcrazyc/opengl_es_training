#include "Shape.h"

DrawParam::DrawParam() {
    vertexPointer = NULL;
    colorPointer = NULL;
    normalPointer = NULL;
    indices = NULL;
}

DrawParam::~DrawParam() {
    if (vertexPointer != NULL) {
        delete[] vertexPointer;
        vertexPointer = NULL;
    }

    if (colorPointer != NULL) {
        delete[] colorPointer;
        colorPointer = NULL;
    }

    if (normalPointer != NULL) {
        delete[] normalPointer;
        normalPointer = NULL;
    }

    if (indices != NULL) {
        delete[] indices;
        indices = NULL;
    }
}

void Shape::SetPos( float x/*=0*/, float y/*=0*/, float z/*=0*/ ) {
    mPosX = x;
    mPosY = y;
    mPosZ = z;
}

void Shape::Update() {
    mAngle += 2.0f;
}

void Shape::Draw() {
    glTranslatef(mPosX, mPosY ,mPosZ);
    glRotatef(mAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(45.0f, 1.0f, 1.0f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for (std::list<DrawParam *>::iterator it=drawList.begin(); it!=drawList.end(); it++) {
        DrawParam *drawParam = *it;

        if (drawParam->drawType == DRAW_ARRAYS) {
            glVertexPointer(3, GL_FLOAT, 0, drawParam->vertexPointer);
            glColorPointer(4, GL_FLOAT, 0, drawParam->colorPointer);
            if (drawParam->normalPointer != NULL) glNormalPointer(GL_FLOAT, 0, drawParam->normalPointer);
            glDrawArrays(drawParam->mode, drawParam->first, drawParam->count);
        } else if (drawParam->drawType == DRAW_ELEMENTS) {
            glVertexPointer(3, GL_FLOAT, 0, drawParam->vertexPointer);
            glColorPointer(4, GL_FLOAT, 0, drawParam->colorPointer);
            if (drawParam->normalPointer != NULL) glNormalPointer(GL_FLOAT, 0, drawParam->normalPointer);
            glDrawElements(drawParam->mode, drawParam->count, drawParam->indicesType, drawParam->indices);
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}


Shape::Shape() {
    mPosX = mPosY = mPosZ = 0.0f;
    mAngle = 0.0f;
}

Shape::~Shape() {
	Clean();
}

void Shape::Clean() {
	for (std::list<DrawParam *>::iterator it=drawList.begin(); it!=drawList.end(); it++) {
		if (*it) {
			delete *it;
			*it = NULL;
		}
	}

	drawList.clear();
}

void Shape::Reset() {

}

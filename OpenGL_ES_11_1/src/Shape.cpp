#include "Shape.h"

DrawParam::DrawParam() {
    vertexPointer = NULL;
    colorPointer = NULL;
    normalPointer = NULL;
    indices = NULL;
	texturePointer = NULL;
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

	if (texturePointer != NULL)
	{
		delete[] texturePointer;
		texturePointer = NULL;
	}
}

void Shape::SetPos( float x/*=0*/, float y/*=0*/, float z/*=0*/ ) {
    mPosX = x;
    mPosY = y;
    mPosZ = z;
}

void Shape::Update() {
    mAngle += 1.0f;
}

void Shape::Draw() {
    glPushMatrix();
	//glRotatef(90.0f, 0.0f, 0.0f, 0.0f);
    glTranslatef(mPosX, mPosY ,mPosZ);
    glRotatef(mAngle, 0.0f, 1.0f, 0.0f);

	if (mTexture)
	{
		mTexture->apply();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for (std::list<DrawParam *>::iterator it=drawList.begin(); it!=drawList.end(); it++) {
        DrawParam *drawParam = *it;

        if (drawParam->drawType == DRAW_ARRAYS) {
            glVertexPointer(3, GL_FLOAT, 0, drawParam->vertexPointer);
            //glColorPointer(4, GL_FLOAT, 0, drawParam->colorPointer);
            if (drawParam->normalPointer != NULL) glNormalPointer(GL_FLOAT, 0, drawParam->normalPointer);
			if (drawParam->texturePointer!= NULL) glTexCoordPointer(2, GL_FLOAT, 0, drawParam->texturePointer);
            glDrawArrays(drawParam->mode, drawParam->first, drawParam->count);
        } else if (drawParam->drawType == DRAW_ELEMENTS) {
            glVertexPointer(3, GL_FLOAT, 0, drawParam->vertexPointer);
            //glColorPointer(4, GL_FLOAT, 0, drawParam->colorPointer);
            if (drawParam->normalPointer != NULL) glNormalPointer(GL_FLOAT, 0, drawParam->normalPointer);
			if (drawParam->texturePointer!= NULL) glTexCoordPointer(2, GL_FLOAT, 0, drawParam->texturePointer);
            glDrawElements(drawParam->mode, drawParam->count, drawParam->indicesType, drawParam->indices);
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();

	/*GLfloat ambientAndDiffuse[] = {0.0, 0.1, 0.9, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);*/
}


Shape::Shape() {
    mPosX = mPosY = mPosZ = 0.0f;
    mAngle = 0.0f;
	mTexture = NULL;
 
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


void Shape::SetTexture(const std::string& thePath)
{
	if (mTexture == NULL)
	{
		mTexture = new Texture(thePath);
		mTexture->load();
	}
}

void Shape::DeleteTexture()
{
	if (mTexture)
	{
		mTexture->unload();
		delete mTexture;
		mTexture = NULL;
	}
}

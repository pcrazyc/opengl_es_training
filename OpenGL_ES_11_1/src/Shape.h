#pragma once

#include "IwGL.h"
#include <list>
#include <string>
#include "Texture.h"

typedef enum _drawType {
    DRAW_ARRAYS,
    DRAW_ELEMENTS
} DRAW_TYPE;

enum E_SHAPE_TYPE
{
	E_CUBE,
	E_CUBOID,
	E_CYLINDER,
	E_SPHERE,
	E_CONE,
};
class DrawParam {
public:
    DrawParam();
    ~DrawParam();
public:
    float *vertexPointer;
    float *colorPointer;
    float *normalPointer;
	float *texturePointer;

    DRAW_TYPE drawType;
    GLenum mode;
    GLint count;

    GLint first;
    
    GLenum indicesType;
    GLubyte *indices;

} ;

class Shape {
public:
    virtual void Update();
    virtual void Draw();
	virtual void SetPos(float x=0, float y=0, float z=0);
	virtual void Reset();
	void SetAngle(float theAngle);
	void SetTexture(const std::string& thePath);
	void DeleteTexture();
    Shape();

	void Clean();
    virtual ~Shape();

protected:
	float mPosX;
	float mPosY;
	float mPosZ;

    std::list<DrawParam *> drawList;
	float		mAngle;
 
	Texture* mTexture;
};
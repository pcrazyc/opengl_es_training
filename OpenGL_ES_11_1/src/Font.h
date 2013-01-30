#pragma once
#include <string>
#include <map>
#include "IwGL.h"

typedef struct _CharMetrics
{
	int tx, ty;
	int width, height;
} tdst_CharMetrics;


typedef std::map<char, tdst_CharMetrics> FontCharsMap;
typedef std::map<char, tdst_CharMetrics>::iterator FontCharsMapIt;
class Font
{
public:
	Font();
	virtual ~Font();

	void Init(std::string theFontFilePath);
	void Destory();
	void DrawText(std::string theTxt, int theX, int theY);

	void SetScale(float theScale);
private:
	void LoadDemoFontRaw(std::string& theImage);
	FontCharsMap mFontCharsMap;

	int		mHeight;
	int		mWidth;
	int		mFontImageWidth;
	int		mFontImageHeight;
	float	mSacle;
	GLuint	mTexture;

	float*	mVertexPointer;
	float*	mTexPointer;

};
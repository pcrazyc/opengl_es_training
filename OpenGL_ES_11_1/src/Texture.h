#pragma once
#include <string>
#include "IwGL.h"
typedef int status;


const status STATUS_OK   = 0;
const status STATUS_KO   = -1;
const status STATUS_EXIT = -2;
class Texture
{
public:
	Texture(const std::string& pPath);
	~Texture();

	std::string getPath();
	int getHeight();
	int getWidth();

	status load();  
	void unload();
	void apply();
//protected:
//	uint8_t* loadImage();

//private:
//	static void callback_read(png_structp pStruct,
//		png_bytep pData, png_size_t pSize);


private:
	//Resource mResource;
	GLuint mTextureId;
	int mWidth, mHeight;
	GLint mFormat;
	std::string mFilePath;
};
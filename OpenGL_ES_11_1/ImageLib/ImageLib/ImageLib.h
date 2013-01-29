#ifndef __IMAGELIB_H__
#define __IMAGELIB_H__

#include <string>

namespace ImageLib
{

//xiezhen@popcap.com.cn - 2012-08-27
enum IMAGE_TYPE {
    IMG_NULL = 0,
    IMG_PNG,
    IMG_JPG,
    IMG_BMP,
    IMG_GIF,
};

extern IMAGE_TYPE GetImageType(void *imgData, char *ext);

class Image
{
public:
	int						mWidth;
	int						mHeight;
	unsigned long*			mBits;

public:
	Image();
	virtual ~Image();

	int						GetWidth();
	int						GetHeight();
	unsigned long*			GetBits();
};

bool WriteJPEGImage(const std::string& theFileName, Image* theImage);
bool WritePNGImage(const std::string& theFileName, Image* theImage );
bool WriteTGAImage(const std::string& theFileName, Image* theImage );
bool WriteBMPImage(const std::string& theFileName, Image* theImage);
extern int gAlphaComposeColor;
extern bool gAutoLoadAlpha;
extern bool gIgnoreJPEG2000Alpha;  // I've noticed alpha in jpeg2000's that shouldn't have alpha so this defaults to true

Image* GetImage(const std::string& theFileName, bool lookForAlphaImage = true );

void InitJPEG2000();
void CloseJPEG2000();
void SetJ2KCodecKey(const std::string& theKey);

}

//xiezhen@popcap.com.cn - 2012-08-15 - struct for bmp
#pragma   pack(push) 
#pragma   pack(1)
typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
typedef struct tagBITMAPFILEHEADER{
	U16 bfType;
	U32 bfSize;
	U16 bfReserved1;
	U16 bfReserved2;
	U32 bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	U32 biSize;
	U32 biWidth;
	U32 biHeight;
	U16 biPlanes;
	U16 biBitCount;
	U32 biCompression;
	U32 biSizeImage;
	U32 biXPelsPerMeter;
	U32 biYPelsPerMeter;
	U32 biClrUsed;
	U32 biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD{
	U8 rgbBlue;
	U8 rgbGreen;
	U8 rgbRed;
	U8 rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO{
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[1];
} BITMAPINFO;

typedef struct tagBITMAP{
	BITMAPFILEHEADER bmpHead;
	BITMAPINFO		 bmpInfo;
} BITMAP;
#pragma   pack(pop)

#endif //__IMAGELIB_H__
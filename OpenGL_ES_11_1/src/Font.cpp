#include "Font.h"
#include "../ImageLib/ImageLib/ImageLib.h"

tdst_CharMetrics MyDefaultFontMerics[256] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 10, 36},
	{3, 1, 5, 36},
	{10, 1, 9, 36},
	{21, 1, 14, 36},
	{37, 1, 13, 36},
	{52, 1, 20, 36},
	{74, 1, 15, 36},
	{91, 1, 4, 36},
	{97, 1, 8, 36},
	{107, 1, 8, 36},
	{117, 1, 10, 36},
	{129, 1, 13, 36},
	{144, 1, 5, 36},
	{151, 1, 6, 36},
	{159, 1, 5, 36},
	{166, 1, 10, 36},
	{178, 1, 13, 36},
	{193, 1, 8, 36},
	{203, 1, 12, 36},
	{217, 1, 13, 36},
	{232, 1, 13, 36},
	{1, 38, 12, 36},
	{15, 38, 12, 36},
	{29, 38, 12, 36},
	{43, 38, 13, 36},
	{58, 38, 11, 36},
	{71, 38, 5, 36},
	{78, 38, 5, 36},
	{85, 38, 12, 36},
	{99, 38, 12, 36},
	{113, 38, 12, 36},
	{127, 38, 12, 36},
	{141, 38, 18, 36},
	{161, 38, 17, 36},
	{180, 38, 11, 36},
	{193, 38, 17, 36},
	{212, 38, 14, 36},
	{228, 38, 10, 36},
	{240, 38, 9, 36},
	{1, 75, 18, 36},
	{21, 75, 13, 36},
	{36, 75, 4, 36},
	{42, 75, 10, 36},
	{54, 75, 13, 36},
	{69, 75, 9, 36},
	{80, 75, 21, 36},
	{103, 75, 14, 36},
	{119, 75, 18, 36},
	{139, 75, 11, 36},
	{152, 75, 19, 36},
	{173, 75, 12, 36},
	{187, 75, 12, 36},
	{201, 75, 10, 36},
	{213, 75, 12, 36},
	{227, 75, 16, 36},
	{1, 112, 21, 36},
	{24, 112, 16, 36},
	{42, 112, 14, 36},
	{58, 112, 12, 36},
	{72, 112, 6, 36},
	{80, 112, 10, 36},
	{92, 112, 6, 36},
	{100, 112, 13, 36},
	{115, 112, 13, 36},
	{130, 112, 8, 36},
	{140, 112, 14, 36},
	{156, 112, 14, 36},
	{172, 112, 14, 36},
	{188, 112, 14, 36},
	{204, 112, 14, 36},
	{220, 112, 8, 36},
	{230, 112, 14, 36},
	{1, 149, 12, 36},
	{15, 149, 5, 36},
	{22, 149, 7, 36},
	{31, 149, 14, 36},
	{47, 149, 4, 36},
	{53, 149, 20, 36},
	{75, 149, 12, 36},
	{89, 149, 14, 36},
	{105, 149, 14, 36},
	{121, 149, 14, 36},
	{137, 149, 7, 36},
	{146, 149, 9, 36},
	{157, 149, 8, 36},
	{167, 149, 12, 36},
	{181, 149, 14, 36},
	{197, 149, 20, 36},
	{219, 149, 14, 36},
	{235, 149, 14, 36},
	{1, 186, 12, 36},
	{15, 186, 9, 36},
	{26, 186, 2, 36},
	{30, 186, 8, 36},
	{40, 186, 13, 36},
	{55, 186, 18, 36},
	{75, 186, 21, 36},
	{98, 186, 21, 36},
	{121, 186, 21, 36},
	{144, 186, 21, 36},
	{167, 186, 29, 36},
	{198, 186, 29, 36},
	{1, 223, 29, 36},
	{32, 223, 29, 36},
	{63, 223, 23, 36},
	{88, 223, 26, 36},
	{116, 223, 28, 36},
	{146, 223, 29, 36},
	{177, 223, 29, 36},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
};
Font::Font()
{
	mVertexPointer = NULL;
	mTexPointer = NULL;
	mHeight = 0;
	mWidth = 0;
	mFontImageWidth = 0;
	mFontImageHeight = 0;
	mSacle = 1.0f;
}

Font::~Font()
{
	Destory();
}

void Font::Init(std::string theFontFilePath)
{
	LoadDemoFontRaw(theFontFilePath);
	int aCharSize = sizeof(MyDefaultFontMerics)/ sizeof(tdst_CharMetrics);
	//assert(aCharSize < 255)
	for (int i = 0; i < aCharSize;i++)
	{
		mFontCharsMap[(char)i]= MyDefaultFontMerics[i];
	}

	mVertexPointer = new float[6*3];
	mTexPointer = new float[6*2];

}

void Font::Destory()
{
	mFontCharsMap.clear();
	if (mVertexPointer)
	{
		delete[] mVertexPointer;
		mVertexPointer = NULL;
	}
	if (mTexPointer)
	{
		delete[] mTexPointer;
		mTexPointer = NULL;
	}
}

void Font::DrawText(std::string theTxt, int theX, int theY)
{
	glBindTexture(GL_TEXTURE_2D, mTexture);		
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc( GL_SRC_ALPHA,GL_ONE);
	float theXDest = (float)theX;
	float theYDest = (float)theY;
	for(int i = 0; i < (int)theTxt.length(); ++i)
	{
		//search char
		char theChar = theTxt[i];
		if(theChar == ' ') //white space
		{
			theXDest += mHeight * 0.4f * mSacle;
			continue;
		}
		if (theChar == '\n')
		{
			theXDest = (float)theX * mSacle;
			theYDest -= mHeight * mSacle;

			continue;
		}
		FontCharsMapIt theCharEntry = mFontCharsMap.find(theChar);
		//if find
		if(mFontCharsMap.end() != theCharEntry)
		{
			tdst_CharMetrics aTest = theCharEntry->second;
			//get char entry inform
			char ch = theCharEntry->first;
			float cx = (float)theCharEntry->second.tx  / mFontImageWidth;
			float cy = (float)theCharEntry->second.ty / mFontImageHeight;
			float cWidth = (float)theCharEntry->second.width / mFontImageWidth;
			float cHeigth = (float)theCharEntry->second.height / mFontImageHeight;

			//0
			mVertexPointer[0] = 0;
			mVertexPointer[1] = 0;
			mVertexPointer[2] = 0;

			//1
			mVertexPointer[3] = 0;
			mVertexPointer[4] = (float)mHeight* mSacle;
			mVertexPointer[5] = 0;

			//2
			mVertexPointer[6] = (float)mWidth* mSacle;
			mVertexPointer[7] = 0;
			mVertexPointer[8] = 0;

			//2
			mVertexPointer[9] = (float)mWidth* mSacle;
			mVertexPointer[10] = 0;
			mVertexPointer[11] = 0;

			//1
			mVertexPointer[12] = 0;
			mVertexPointer[13] = (float)mHeight* mSacle;
			mVertexPointer[14] = 0;

			//3
			mVertexPointer[15] = (float)mWidth* mSacle;
			mVertexPointer[16] = (float)mHeight* mSacle;
			mVertexPointer[17] = 0;

			////0
			mTexPointer[0] = cx;
			mTexPointer[1] = cy + cHeigth;

			//1
			mTexPointer[2] = cx ;
			mTexPointer[3] = cy ;

			//2
			mTexPointer[4] = cx + cWidth;
			mTexPointer[5] = cy + cHeigth;

			//2
			mTexPointer[6] = cx + cWidth;
			mTexPointer[7] = cy + cHeigth ;

			//1
			mTexPointer[8] = cx ;
			mTexPointer[9] = cy ;

			//3
			mTexPointer[10] = cx + cWidth;
			mTexPointer[11] = cy ;
	

			//draw ch here
			glPushMatrix();
			//glEnable(GL_BLEND);
			glTranslatef(theXDest, theYDest, 0);
			glVertexPointer(3, GL_FLOAT, 0, mVertexPointer);
			glTexCoordPointer(2,GL_FLOAT, 0, mTexPointer);
	

			glDrawArrays(GL_TRIANGLES, 0, 6);
			//glDisable(GL_BLEND);
			glPopMatrix();
			theXDest += (mWidth + mHeight * 0.125f) * mSacle;
		}
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);


}

void Font::SetScale(float theScale)
{
	mSacle = theScale;
}

//the demo raw file is 256*256*4, rgba.
void Font::LoadDemoFontRaw(std::string& theImage)
{
	FILE* img = NULL;
	img = fopen(theImage.c_str(),"rb");
	//font info
	mHeight = 36;
	mWidth = 36;
	mFontImageWidth = 256;
	mFontImageHeight = 256;

	int size = 256*256*4;  

	//unsigned char *data = (unsigned char*)malloc(size);
	unsigned char *data = new unsigned char[size];

	fseek(img,0,SEEK_SET);    // image data
	fread(data,size,1,img);

	fclose(img);

	//// Set our flip buffer (explained in for loop)
	//unsigned char* aDataBuffer = new unsigned char[size];
	//debug
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bWidth, bHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		GL_CLAMP_TO_EDGE);
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFontImageWidth, mFontImageHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mFontImageWidth, mFontImageHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	if (data)
		delete [] data;

}
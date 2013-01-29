#define XMD_H

///#define USE_TWIN_HEAPS	1
//#include <windows.h>

#include "ImageLib.h"
#include "byteswap.h"
#include "png/png.h"
#include <math.h>

#include "s3eFile.h"
#include "s3eMemory.h"

typedef unsigned char       BYTE;
typedef unsigned short      WORD;

extern "C"
{
#include "jpeg/jpeglib.h"
}
//#include "Common.h"
using namespace ImageLib;

// iPhone uses RGBA
#define MAKE_PIXEL( r, g, b, a )    ( ((a) << 24) | ((b) << 16) | ((g) << 8) | (r) )

//xiezhen@popcap.com.cn - 2012-8-27 - just differentiate png, jpg, bmp, gif. 
namespace ImageLib {
    IMAGE_TYPE GetImageType( void *imgData, char *ext ) {
        char cBuffer = *(char *)imgData;
        IMAGE_TYPE imgType = IMG_NULL;
        if (cBuffer == 0x89) {
            imgType = IMG_PNG;
            if (ext != NULL)
                strcpy(ext, "png");
        } else if (cBuffer == 0x47) {
            imgType = IMG_GIF;
            if (ext != NULL)
                strcpy(ext, "gif");
        } else if (cBuffer == 0x42) {
            imgType = IMG_BMP;
            if (ext != NULL)
                strcpy(ext, "bmp");
        } else if (cBuffer == 0xff) {
            imgType = IMG_JPG;
            if (ext != NULL)
                strcpy(ext, "jpg");
        }
        return imgType;
    }
}

Image* GetTGAImage(const std::string& theFileName );
Image* GetPNGImage(const std::string& theFileName );
Image* GetJPEGImage(const std::string& theFileName );
Image* GetJPEG2000Image(const std::string& theFileName );
Image* GetGIFImage(const std::string& theFileName );
Image* GetBMPImage(const std::string& theFileName);
//IMAGE_TYPE GetImageType(const std::string& theFileName);

Image::Image()
{
	mWidth = 0;
	mHeight = 0;
	mBits = NULL;
//	mImage = NULL;
}

Image::~Image()
{
	delete mBits;

//	if( mImage )
//	{
//		delete mImage;
//	}
}

int	Image::GetWidth()
{
	return mWidth;
}

int	Image::GetHeight()
{	
	return mHeight;
}

unsigned long* Image::GetBits()
{
	return mBits;
}

Image* GetPNGImage(const std::string& theFileName )
{
	
#if FALSE
	Image*  anImage;
	CIwImage* img;

	if( !s3eFileCheckExists( theFileName.c_str() ) )
	{
		return NULL;
	}


	img = new CIwImage();	

	s3eFile* pFile = s3eFileOpen( theFileName.c_str(), "rb" );
	img->ReadFile( pFile );

	if( pFile )
	{
		anImage = new Image();
		anImage->mImage = img;
		anImage->mWidth = anImage->mImage->GetWidth();
		anImage->mHeight =anImage-> mImage->GetHeight();
		uint8* texels = anImage->mImage->GetTexels();
		anImage->mBits = (unsigned long*)texels;
	}

	return anImage;
#else
	
	//akelly - test
	if( !s3eFileCheckExists( theFileName.c_str() ) )
	{
		return NULL;
	}

	png_structp png_ptr;
	png_infop info_ptr;
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;
	s3eFile *fp;

	
    if ((fp = s3eFileOpen(theFileName.c_str(), "rb")) == NULL)
			return NULL;
	
	
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
	  NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		s3eFileClose(fp);
		return NULL;
	}

	/* Allocate/initialize the memory for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		s3eFileClose(fp);
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return NULL;
	}
	
   /* Set error handling if you are using the setjmp/longjmp method (this is
    * the normal method of doing things with libpng).  REQUIRED unless you
    * set up your own error handlers in the png_create_read_struct() earlier.
    */
	if (setjmp(png_ptr->jmpbuf))
	{
		/* Free all of the memory associated with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		s3eFileClose(fp);
		/* If we get here, we had a problem reading the file */
		return NULL;
	}
	
	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);
	
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
       &interlace_type, NULL, NULL);
	
#ifdef DEBUG
    if( interlace_type != PNG_INTERLACE_NONE )
    {
        printf("ImageLib: WARNING - %s is an interlaced PNG.\n", theFileName.c_str() );
    }
    
    if( bit_depth != 8 )
    {
        printf("ImageLib: WARNING - %s has the wrong bit-depth.\n", theFileName.c_str() );
    }
    
#endif

	/* Add filler (or alpha) byte (before/after each RGB triplet) */
	png_set_expand(png_ptr);
	
#ifdef PLATFORM_BIG_ENDIAN
	png_set_filler(png_ptr, 0xff, PNG_FILLER_BEFORE);
	png_set_swap_alpha(png_ptr);
#else
	png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
#endif
	
	//png_set_gray_1_2_4_to_8(png_ptr);
	png_set_palette_to_rgb(png_ptr);
	png_set_gray_to_rgb(png_ptr);
    
    // We want RGBA for OpenGL
#ifndef PLATFORM_BIG_ENDIAN
//	png_set_bgr(png_ptr);
#endif

    int number_passes = png_set_interlace_handling(png_ptr);
//	int aNumBytes = png_get_rowbytes(png_ptr, info_ptr) * height;
	int aNumLongs = width*height;
//printf("png ifo %d %d %d %d\n",width,height,aNumBytes,aNumLongs);

	unsigned long* aBits = new unsigned long[aNumLongs];
    while (number_passes-- > 0 )
    {
        for (unsigned int i = 0; i < height; i++)
        {
            png_bytep anAddr = (png_bytep) &aBits[i*width];
            png_read_rows(png_ptr, (png_bytepp) &anAddr, NULL, 1);
        }
    }
    
	/* read rest of file, and get additional chunks in info_ptr - REQUIRED */
	png_read_end(png_ptr, info_ptr);

	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
	
	/* close the file */
	s3eFileClose(fp);

	Image* anImage = new Image();
	anImage->mWidth = width;
	anImage->mHeight = height;
	anImage->mBits = aBits;
	
	return anImage;
#endif
}



Image* GetTGAImage(const std::string& theFileName )
{
	//printf( "\nThis is a TGA Image\n" );

	//akelly - test
	if( !s3eFileCheckExists( theFileName.c_str() ) )
	{
		return NULL;
	}

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	FILE* aTGAFile = NULL;	
    aTGAFile = fopen(theFileName.c_str(), "rb");
#else
	s3eFile* aTGAFile = NULL;
	aTGAFile = s3eFileOpen(theFileName.c_str(), "rb");
#endif


    if (aTGAFile == NULL)
        return NULL;
    
	BYTE aHeaderIDLen;	
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aHeaderIDLen, sizeof(BYTE), 1, aTGAFile);
#else
	s3eFileRead(&aHeaderIDLen, sizeof(BYTE), 1, aTGAFile);
#endif

	BYTE aColorMapType;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aColorMapType, sizeof(BYTE), 1, aTGAFile);
#else
	s3eFileRead(&aColorMapType, sizeof(BYTE), 1, aTGAFile);
#endif

	BYTE anImageType;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&anImageType, sizeof(BYTE), 1, aTGAFile);
#else
	s3eFileRead(&anImageType, sizeof(BYTE), 1, aTGAFile);
#endif
	

	WORD aFirstEntryIdx;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aFirstEntryIdx, sizeof(WORD), 1, aTGAFile);
#else
	s3eFileRead(&aFirstEntryIdx, sizeof(WORD), 1, aTGAFile);
#endif
	FixBytes(aFirstEntryIdx);

	WORD aColorMapLen;	
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aColorMapLen, sizeof(WORD), 1, aTGAFile);
#else
	s3eFileRead(&aColorMapLen, sizeof(WORD), 1, aTGAFile);
#endif
	FixBytes(aColorMapLen);

	BYTE aColorMapEntrySize;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aColorMapEntrySize, sizeof(BYTE), 1, aTGAFile);	
#else
	s3eFileRead(&aColorMapEntrySize, sizeof(BYTE), 1, aTGAFile);	
#endif

	WORD anXOrigin;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&anXOrigin, sizeof(WORD), 1, aTGAFile);
#else
	s3eFileRead(&anXOrigin, sizeof(WORD), 1, aTGAFile);
#endif
	FixBytes(anXOrigin);

	WORD aYOrigin;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aYOrigin, sizeof(WORD), 1, aTGAFile);
#else
	s3eFileRead(&aYOrigin, sizeof(WORD), 1, aTGAFile);
#endif	
	FixBytes(aYOrigin);

	WORD anImageWidth;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&anImageWidth, sizeof(WORD), 1, aTGAFile);
#else
	s3eFileRead(&anImageWidth, sizeof(WORD), 1, aTGAFile);
#endif	
	FixBytes(anImageWidth);

	WORD anImageHeight;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&anImageHeight, sizeof(WORD), 1, aTGAFile);
#else
	s3eFileRead(&anImageHeight, sizeof(WORD), 1, aTGAFile);
#endif	
	FixBytes(anImageHeight);

	BYTE aBitCount = 32;
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&aBitCount, sizeof(BYTE), 1, aTGAFile);
#else
	s3eFileRead(&aBitCount, sizeof(BYTE), 1, aTGAFile);
#endif	
	
	BYTE anImageDescriptor = 8 | (1<<5);
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&anImageDescriptor, sizeof(BYTE), 1, aTGAFile);
#else
	s3eFileRead(&anImageDescriptor, sizeof(BYTE), 1, aTGAFile);
#endif	
	
	if ((aBitCount != 32) ||
		(anImageDescriptor != (8 | (1<<5))))
	{
#if FALSE
		fclose(aTGAFile);
#else
		s3eFileClose(aTGAFile);
#endif	
		return NULL;
	}

	Image* anImage = new Image();

	anImage->mWidth = anImageWidth;
	anImage->mHeight = anImageHeight;
	anImage->mBits = new unsigned long[anImageWidth*anImageHeight];
	
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(anImage->mBits, 4, anImage->mWidth*anImage->mHeight, aTGAFile);
#else
	s3eFileRead(anImage->mBits, 4, anImage->mWidth*anImage->mHeight, aTGAFile);
#endif	

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fclose(aTGAFile);
#else
	s3eFileClose(aTGAFile);
#endif	
	
#ifdef PLATFORM_BIG_ENDIAN
	unsigned long	*pPixel = anImage->mBits;
	for(int i = 0; i < (anImageWidth*anImageHeight); i++)
	{
		FixBytes(*pPixel);
		pPixel++;;
	}
#endif	

	return anImage;
}

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
static int ReadBlobBlock(FILE* fp, char* data)
{
	unsigned char aCount = 0;
	fread(&aCount, sizeof(char), 1, fp);
	fread(data, sizeof(char), aCount, fp);
	return aCount;
}
#else
static int ReadBlobBlock(s3eFile* fp, char* data)
{
	unsigned char aCount = 0;
	s3eFileRead(&aCount, sizeof(char), 1, fp);
	s3eFileRead(data, sizeof(char), aCount, fp);
	return aCount;
}
#endif

Image* GetGIFImage(const std::string& theFileName )
{
	//printf( "\nThis is a GIF Image\n" );

	//akelly - test
	if( !s3eFileCheckExists( theFileName.c_str() ) )
	{
		return NULL;
	}

	#define BitSet(byte,bit)  (((byte) & (bit)) == (bit))
	#define LSBFirstOrder(x,y)  (((y) << 8) | (x))

	int
		opacity,
		status;

	register int i;

	register unsigned char *p;

	unsigned char
		background,
		c,
		flag,
		*global_colormap,
		header[1664],
		magick[12];

	unsigned int
		delay,
		dispose,
		global_colors,
		image_count,
		iterations;

	/*
	Open image file.
	*/

//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	FILE *fp;
	if ((fp = fopen(theFileName.c_str(), "rb")) == NULL)
        return NULL;
#else
	s3eFile *fp;
	if ((fp = s3eFileOpen(theFileName.c_str(), "rb")) == NULL)
        return NULL;
#endif

	/*
	Determine if this is a GIF file.
	*/
//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	status=fread(magick, sizeof(char), 6, fp);
#else
	status=s3eFileRead(magick, sizeof(char), 6, fp);
#endif

	if (((strncmp((char *) magick,"GIF87",5) != 0) &&
		(strncmp((char *) magick,"GIF89",5) != 0)))
		{
#if FALSE
			fclose(fp);
#else
			s3eFileClose( fp );
#endif
			return NULL;
		}

	global_colors=0;
	global_colormap=(unsigned char *) NULL;

	short pw;
	short ph;

//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fread(&pw, sizeof(short), 1, fp);
	fread(&ph, sizeof(short), 1, fp);
	fread(&flag, sizeof(char), 1, fp);
	fread(&background, sizeof(char), 1, fp);
	fread(&c, sizeof(char), 1, fp);
#else
	s3eFileRead(&pw, sizeof(short), 1, fp);
	s3eFileRead(&ph, sizeof(short), 1, fp);
	s3eFileRead(&flag, sizeof(char), 1, fp);
	s3eFileRead(&background, sizeof(char), 1, fp);
	s3eFileRead(&c, sizeof(char), 1, fp);
#endif

	if (BitSet(flag,0x80))
	{
		/*
		opacity global colormap.
		*/
		global_colors=1 << ((flag & 0x07)+1);
		global_colormap=new unsigned char[3*global_colors];
		if (global_colormap == (unsigned char *) NULL)
		{
#if FALSE
			fclose(fp);
#else
			s3eFileClose( fp );
#endif
			return NULL;
		}
//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fread(global_colormap, sizeof(char), 3*global_colors, fp);
#else
		s3eFileRead(global_colormap, sizeof(char), 3*global_colors, fp);
#endif
	}

	delay=0;
	dispose=0;
	iterations=1;
	opacity=(-1);
	image_count=0;

	for ( ; ; )
	{
//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		if (fread(&c, sizeof(char), 1, fp) == 0)
		break;
#else
		if (s3eFileRead(&c, sizeof(char), 1, fp) == 0)
		break;
#endif

		if (c == ';')
		break;  /* terminator */
		if (c == '!')
		{
			/*
			GIF Extension block.
			*/
//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
			fread(&c, sizeof(char), 1, fp);
#else
			s3eFileRead(&c, sizeof(char), 1, fp);
#endif

			switch (c)
			{
			case 0xf9:
				{
					/*
					Read Graphics Control extension.
					*/
					while (ReadBlobBlock(fp,(char *) header) > 0);

					dispose=header[0] >> 2;
					delay=(header[2] << 8) | header[1];
					if ((header[0] & 0x01) == 1)
					opacity=header[3];
					break;
				}
			case 0xfe:
				{
					char *comments;
					int length;

					/*
					Read Comment extension.
					*/
					comments=(char *) NULL;
					for ( ; ; )
					{
						length=ReadBlobBlock(fp,(char *) header);
						if (length <= 0)
						break;
						if (comments == NULL)
						{
							comments= new char[length+1];
							if (comments != (char *) NULL)
							*comments='\0';
						}

						header[length]='\0';
						strcat(comments,(char *) header);
					}
					if (comments == (char *) NULL)
						break;

					delete[] comments;
					break;
				}
			case 0xff:
				{
					int
					loop;

					/*
					Read Netscape Loop extension.
					*/
					loop=false;
					if (ReadBlobBlock(fp,(char *) header) > 0)
					loop=!strncmp((char *) header,"NETSCAPE2.0",11);
					while (ReadBlobBlock(fp,(char *) header) > 0)
					if (loop)
					iterations=(header[2] << 8) | header[1];
					break;
				}
			default:
				{
					while (ReadBlobBlock(fp,(char *) header) > 0);
					break;
				}
			}
		}

		if (c != ',')
			continue;

		if (image_count != 0)
		{
			/*
			Allocate next image structure.
			*/

			/*AllocateNextImage(image_info,image);
			if (image->next == (Image *) NULL)
			{
			DestroyImages(image);
			return((Image *) NULL);
			}
			image=image->next;
			MagickMonitor(LoadImagesText,TellBlob(image),image->filesize);*/
		}
		image_count++;

		signed short pagex;
		signed short pagey;
		signed short width;
		signed short height;
		int colors;
		bool interlaced;

//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fread(&pagex, sizeof(short), 1, fp);
		fread(&pagey, sizeof(short), 1, fp);
		fread(&width, sizeof(short), 1, fp);
		fread(&height, sizeof(short), 1, fp);
		fread(&flag, sizeof(char), 1, fp);
#else
		s3eFileRead(&pagex, sizeof(short), 1, fp);
		s3eFileRead(&pagey, sizeof(short), 1, fp);
		s3eFileRead(&width, sizeof(short), 1, fp);
		s3eFileRead(&height, sizeof(short), 1, fp);
		s3eFileRead(&flag, sizeof(char), 1, fp);
#endif
		FixBytes(pagex);
		FixBytes(pagey);
		FixBytes(width);
		FixBytes(height);

		colors=!BitSet(flag,0x80) ? global_colors : 1 << ((flag & 0x07)+1);
		unsigned long* colortable = new unsigned long[colors];

		interlaced = BitSet(flag,0x40);

		delay=0;
		dispose=0;
		iterations=1;
		/*if (image_info->ping)
		{
		f (opacity >= 0)
		/image->matte=true;

		CloseBlob(image);
		return(image);
		}*/
		if ((width == 0) || (height == 0))
		{
			delete[] colortable;
			return NULL;
		}
		/*
		Inititialize colormap.
		*/
		/*if (!AllocateImageColormap(image,image->colors))
		ThrowReaderException(ResourceLimitWarning,"Memory allocation failed",
		image);*/
		if (!BitSet(flag,0x80))
		{
			/*
			Use global colormap.
			*/
			p=global_colormap;
			for (i=0; i < (int) colors; i++)
			{
				int r = *p++;
				int g = *p++;
				int b = *p++;

//				colortable[i] = 0xFF000000 | (r << 16) | (g << 8) | (b);
                colortable[i] = MAKE_PIXEL( r,g,b,0xff); // dbanay
			}

			//image->background_color=
			//image->colormap[Min(background,image->colors-1)];
		}
		else
		{
			unsigned char
			*colormap;

			/*
			Read local colormap.
			*/
			colormap=new unsigned char[3*colors];
//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
			fread(colormap, sizeof(char), 3*colors, fp);
#else
			s3eFileRead(colormap, sizeof(char), 3*colors, fp);
#endif

			p=colormap;
			for (i=0; i < (int) colors; i++)
			{
				int r = *p++;
				int g = *p++;
				int b = *p++;

				colortable[i] = MAKE_PIXEL( r,g,b,0xff);
			}
			delete[] colormap;
		}

		/*if (opacity >= (int) colors)
		{
		for (i=colors; i < (opacity+1); i++)
		{
		image->colormap[i].red=0;
		image->colormap[i].green=0;
		image->colormap[i].blue=0;
		}
		image->colors=opacity+1;
		}*/
		/*
		Decode image.
		*/
		//status=DecodeImage(image,opacity,exception);

		//if (global_colormap != (unsigned char *) NULL)
		// LiberateMemory((void **) &global_colormap);
		if (global_colormap != NULL)
		{
			delete [] global_colormap;
			global_colormap = NULL;
		}

		//while (image->previous != (Image *) NULL)
		//    image=image->previous;

		#define MaxStackSize  4096
		#define NullCode  (-1)

		int
			available,
			bits,
			code,
			clear,
			code_mask,
			code_size,
			count,
			end_of_information,
			in_code,
			offset,
			old_code,
			pass,
			y;

		register int
			x;

		register unsigned int
			datum;

		short
			*prefix;

		unsigned char
			data_size,
			first,
			*packet,
			*pixel_stack,
			*suffix,
			*top_stack;

		/*
		Allocate decoder tables.
		*/

		packet=new unsigned char[256];
		prefix=new short[MaxStackSize];
		suffix=new unsigned char [MaxStackSize];
		pixel_stack= new unsigned char[MaxStackSize+1];

		/*
		Initialize GIF data stream decoder.
		*/
		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fread(&data_size, sizeof(char), 1, fp);
#else
		s3eFileRead(&data_size, sizeof(char), 1, fp);
#endif
		
		clear=1 << data_size;
		end_of_information=clear+1;
		available=clear+2;
		old_code=NullCode;
		code_size=data_size+1;
		code_mask=(1 << code_size)-1;
		for (code=0; code < clear; code++)
		{
			prefix[code]=0;
			suffix[code]=(unsigned char) code;
		}
		/*
		Decode GIF pixel stream.
		*/
		datum=0;
		bits=0;
		c=0;
		count=0;
		first=0;
		offset=0;
		pass=0;
		top_stack=pixel_stack;

		unsigned long* aBits = new unsigned long[width*height];

		register unsigned char *c = NULL;

		for (y=0; y < (int) height; y++)
		{
			//q=SetImagePixels(image,0,offset,width,1);
			//if (q == (PixelPacket *) NULL)
			//break;
			//indexes=GetIndexes(image);

			unsigned long* q = aBits + offset*width;



			for (x=0; x < (int) width; )
			{
				if (top_stack == pixel_stack)
				{
					if (bits < code_size)
					{
						/*
						Load bytes until there is enough bits for a code.
						*/
						if (count == 0)
						{
							/*
							Read a new data block.
							*/
							count=ReadBlobBlock(fp,(char *) packet);
							if (count <= 0)
							break;
							c=packet;
						}
						datum+=(*c) << bits;
						bits+=8;
						c++;
						count--;
						continue;
					}
					/*
					Get the next code.
					*/
					code=datum & code_mask;
					datum>>=code_size;
					bits-=code_size;
					/*
					Interpret the code
					*/
					if ((code > available) || (code == end_of_information))
					break;
					if (code == clear)
					{
						/*
						Reset decoder.
						*/
						code_size=data_size+1;
						code_mask=(1 << code_size)-1;
						available=clear+2;
						old_code=NullCode;
						continue;
					}
					if (old_code == NullCode)
					{
						*top_stack++=suffix[code];
						old_code=code;
						first=(unsigned char) code;
						continue;
					}
					in_code=code;
					if (code >= available)
					{
						*top_stack++=first;
						code=old_code;
					}
					while (code >= clear)
					{
						*top_stack++=suffix[code];
						code=prefix[code];
					}
					first=suffix[code];
					/*
					Add a new string to the string table,
					*/
					if (available >= MaxStackSize)
						break;
					*top_stack++=first;
					prefix[available]=old_code;
					suffix[available]=first;
					available++;
					if (((available & code_mask) == 0) && (available < MaxStackSize))
					{
						code_size++;
						code_mask+=available;
					}
					old_code=in_code;
				}
				/*
				Pop a pixel off the pixel stack.
				*/
				top_stack--;

				int index=(*top_stack);

				*q=colortable[index];

				if (index == opacity)
					*q = 0;

				x++;
				q++;
			}

			if (!interlaced)
				offset++;
			else
			{
				switch (pass)
				{
				case 0:
				default:
					{
						offset+=8;
						if (offset >= height)
						{
							pass++;
							offset=4;
						}
						break;
					}
				case 1:
					{
						offset+=8;
						if (offset >= height)
						{
							pass++;
							offset=2;
						}
						break;
					}
				case 2:
					{
						offset+=4;
						if (offset >= height)
						{
							pass++;
							offset=1;
						}
						break;
					}
				case 3:
					{
						offset+=2;
						break;
					}
				}
			}

			if (x < width)
				break;

			/*if (image->previous == (Image *) NULL)
			if (QuantumTick(y,image->rows))
			MagickMonitor(LoadImageText,y,image->rows);*/
		}
		delete[] pixel_stack;
		delete[] suffix;
		delete[] prefix;
		delete[] packet;

		delete[] colortable;

		//if (y < image->rows)
		//failed = true;

		Image* anImage = new Image();

		anImage->mWidth = width;
		anImage->mHeight = height;
		anImage->mBits = aBits;

		//TODO: Change for animation crap
		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose(fp);
#else
		s3eFileClose( fp );
#endif
		return anImage;
	}

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	fclose(fp);
#else
	s3eFileClose( fp );
#endif

	return NULL;
}

typedef struct my_error_mgr * my_error_ptr;

struct my_error_mgr
{
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);

}

bool ImageLib::WriteJPEGImage(const std::string& theFileName, Image* theImage)
{
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	FILE *fp;
	if ((fp = fopen(theFileName.c_str(), "wb")) == NULL)
		return false;
#else	
	s3eFile *fp;
	if ((fp = s3eFileOpen(theFileName.c_str(), "wb")) == NULL)
		return false;
#endif

	struct jpeg_compress_struct cinfo;
	struct my_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;

	if (setjmp(jerr.setjmp_buffer))
	{
		/* If we get here, the JPEG code has signaled an error.
		 * We need to clean up the JPEG object, close the input file, and return.
		 */
		jpeg_destroy_compress(&cinfo);
	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose( fp );
#else
		s3eFileClose( fp );
#endif
		return false;
	}

	jpeg_create_compress(&cinfo);

	cinfo.image_width = theImage->mWidth;
	cinfo.image_height = theImage->mHeight;
	cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    cinfo.optimize_coding = 1;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 80, TRUE);

	jpeg_stdio_dest(&cinfo, fp);

	jpeg_start_compress(&cinfo, true);

	int row_stride = theImage->GetWidth() * 3;

	unsigned char* aTempBuffer = new unsigned char[row_stride];

	unsigned long* aSrcPtr = theImage->mBits;

	for (int aRow = 0; aRow < theImage->mHeight; aRow++)
	{
		unsigned char* aDest = aTempBuffer;

		for (int aCol = 0; aCol < theImage->mWidth; aCol++)
		{
			unsigned long src = *(aSrcPtr++);

			*aDest++ = (src >> 16) & 0xFF;
			*aDest++ = (src >>  8) & 0xFF;
			*aDest++ = (src      ) & 0xFF;
		}

		jpeg_write_scanlines(&cinfo, &aTempBuffer, 1);
	}

	delete [] aTempBuffer;

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose( fp );
#else
		s3eFileClose( fp );
#endif

	return true;
}

bool ImageLib::WritePNGImage(const std::string& theFileName, Image* theImage )
{
	png_structp png_ptr;
	png_infop info_ptr;

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	FILE *fp;
	if ((fp = fopen(theFileName.c_str(), "wb")) == NULL)
			return false;
#else
	s3eFile *fp;
	if ((fp = s3eFileOpen(theFileName.c_str(), "wb")) == NULL)
			return false;
#endif

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
	  NULL, NULL, NULL);

	if (png_ptr == NULL)
	{
		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose(fp);
#else
		s3eFileClose(fp);
#endif
		return false;
	}

	// Allocate/initialize the memory for image information.  REQUIRED.
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose(fp);
#else
		s3eFileClose(fp);
#endif
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return false;
	}

   // Set error handling if you are using the setjmp/longjmp method (this is
   // the normal method of doing things with libpng).  REQUIRED unless you
   // set up your own error handlers in the png_create_write_struct() earlier.

	if (setjmp(png_ptr->jmpbuf))
	{
		// Free all of the memory associated with the png_ptr and info_ptr
		png_destroy_write_struct(&png_ptr, &info_ptr);
		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose(fp);
#else
		s3eFileClose(fp);
#endif
		// If we get here, we had a problem writeing the file
		return NULL;
	}

	png_init_io(png_ptr, fp);

	
	png_color_8 sig_bit;
	sig_bit.red = 8;
	sig_bit.green = 8;
	sig_bit.blue = 8;
	/* if the image has an alpha channel then */
	sig_bit.alpha = 8;
	png_set_sBIT(png_ptr, info_ptr, &sig_bit);
#ifdef PLATFORM_BIG_ENDIAN
	png_set_swap_alpha(png_ptr);
#else
	png_set_bgr(png_ptr);
#endif

	png_set_IHDR(png_ptr, info_ptr, theImage->mWidth, theImage->mHeight, 8, PNG_COLOR_TYPE_RGB_ALPHA,
       PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Add filler (or alpha) byte (before/after each RGB triplet)
	//png_set_expand(png_ptr);
	//png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	//png_set_gray_1_2_4_to_8(png_ptr);
	//png_set_palette_to_rgb(png_ptr);
	//png_set_gray_to_rgb(png_ptr);

	png_write_info(png_ptr, info_ptr);

	for (int i = 0; i < theImage->mHeight; i++)
	{
		png_bytep aRowPtr = (png_bytep) (theImage->mBits + i*theImage->mWidth);
		png_write_rows(png_ptr, &aRowPtr, 1);
	}

	// write rest of file, and get additional chunks in info_ptr - REQUIRED
	png_write_end(png_ptr, info_ptr);

	// clean up after the write, and free any memory allocated - REQUIRED
	png_destroy_write_struct(&png_ptr, &info_ptr);

	// close the file
		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose(fp);
#else
		s3eFileClose(fp);
#endif

	return true;
}

bool ImageLib::WriteTGAImage(const std::string& theFileName, Image* theImage )
{
	FILE*	aTGAFile;
	

		aTGAFile = fopen(theFileName.c_str(), "wb");
		if (aTGAFile == NULL)
			return false;

	
	BYTE aHeaderIDLen = 0;
	fwrite(&aHeaderIDLen, sizeof(BYTE), 1, aTGAFile);

	BYTE aColorMapType = 0;
	fwrite(&aColorMapType, sizeof(BYTE), 1, aTGAFile);
	
	BYTE anImageType = 2;
	fwrite(&anImageType, sizeof(BYTE), 1, aTGAFile);

	WORD aFirstEntryIdx = 0;
	fwrite(&aFirstEntryIdx, sizeof(WORD), 1, aTGAFile);

	WORD aColorMapLen = 0;
	fwrite(&aColorMapLen, sizeof(WORD), 1, aTGAFile);

	BYTE aColorMapEntrySize = 0;
	fwrite(&aColorMapEntrySize, sizeof(BYTE), 1, aTGAFile);	

	WORD anXOrigin = 0;
	fwrite(&anXOrigin, sizeof(WORD), 1, aTGAFile);

	WORD aYOrigin = 0;
	fwrite(&aYOrigin, sizeof(WORD), 1, aTGAFile);

	WORD anImageWidth = theImage->mWidth;
	FixBytes(anImageWidth);
	fwrite(&anImageWidth, sizeof(WORD), 1, aTGAFile);	

	WORD anImageHeight = theImage->mHeight;
	FixBytes(anImageHeight);
	fwrite(&anImageHeight, sizeof(WORD), 1, aTGAFile);	

	BYTE aBitCount = 32;
	fwrite(&aBitCount, sizeof(BYTE), 1, aTGAFile);	

	BYTE anImageDescriptor = 8 | (1<<5);
	fwrite(&anImageDescriptor, sizeof(BYTE), 1, aTGAFile);

#ifdef PLATFORM_BIG_ENDIAN
	unsigned long	*pPixel = theImage->mBits;
	for(int i = 0; i < (theImage->mWidth*theImage->mHeight); i++)
	{
		FixBytes(*pPixel);
		pPixel++;;
	}
#endif	

	fwrite(theImage->mBits, 4, theImage->mWidth*theImage->mHeight, aTGAFile);

	fclose(aTGAFile);

	return true;
}

#ifdef  _WIN32
bool ImageLib::WriteBMPImage(const std::string& theFileName, Image* theImage)
{
	FILE* aFile = fopen(theFileName.c_str(), "wb");
	if (aFile == NULL)
		return false;

	BITMAPFILEHEADER aFileHeader;
	BITMAPINFOHEADER aHeader;

	memset(&aFileHeader,0,sizeof(aFileHeader));
	memset(&aHeader,0,sizeof(aHeader));

	int aNumBytes = theImage->mWidth*theImage->mHeight*4;

	aFileHeader.bfType = ('M'<<8) | 'B';
	aFileHeader.bfSize = sizeof(aFileHeader) + sizeof(aHeader) + aNumBytes;
	aFileHeader.bfOffBits = sizeof(aHeader); 

	aHeader.biSize = sizeof(aHeader);
	aHeader.biWidth = theImage->mWidth;
	aHeader.biHeight = theImage->mHeight;
	aHeader.biPlanes = 1;
	aHeader.biBitCount = 32;
	aHeader.biCompression = BI_RGB;

	fwrite(&aFileHeader,sizeof(aFileHeader),1,aFile);
	fwrite(&aHeader,sizeof(aHeader),1,aFile);
	DWORD *aRow = theImage->mBits + (theImage->mHeight-1)*theImage->mWidth;
	int aRowSize = theImage->mWidth*4;
	for (int i=0; i<theImage->mHeight; i++, aRow-=theImage->mWidth)
		fwrite(aRow,4,theImage->mWidth,aFile);

	fclose(aFile);
	return true;
}
#endif

Image* GetJPEGImage(const std::string& theFileName )
{
	//printf( "\nThis is a JPEG Image\n" );
	//akelly - test
	if( !s3eFileCheckExists( theFileName.c_str() ) )
	{
		return NULL;
	}

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
	FILE *fp;
	if ((fp = fopen(theFileName.c_str(), "rb")) == NULL)
		return NULL;
#else
	s3eFile *fp;
	if ((fp = s3eFileOpen(theFileName.c_str(), "rb")) == NULL)
		return NULL;
#endif

	
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;

	if (setjmp(jerr.setjmp_buffer))
	{
		/* If we get here, the JPEG code has signaled an error.
		 * We need to clean up the JPEG object, close the input file, and return.
		 */
		jpeg_destroy_decompress(&cinfo);

		//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose( fp );
#else
		s3eFileClose( fp );
#endif
		return 0;
	}

	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, TRUE);
    /* Have libjpeg handle any necessary color conversion */
    cinfo.out_color_space = JCS_RGB;
	jpeg_start_decompress(&cinfo);
	int row_stride = cinfo.output_width * cinfo.output_components;

	unsigned char** buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	unsigned long* aBits = new unsigned long[cinfo.output_width*cinfo.output_height];
	unsigned long* q = aBits;

	while (cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);

		unsigned char* p = *buffer;
		for (unsigned int i = 0; i < cinfo.output_width; i++)
		{
			int r = *p++;
			int g = *p++;
			int b = *p++;

            *q++ = MAKE_PIXEL( r, g, b, 0xff );
            
            
		}
	}

	Image* anImage = new Image();
	anImage->mWidth = cinfo.output_width;
	anImage->mHeight = cinfo.output_height;
	anImage->mBits = aBits;

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	//akelly@popcap.com - 2011-01-10 - To speed up Airplay loading on device.
#if FALSE
		fclose( fp );
#else
		s3eFileClose( fp );
#endif

	return anImage;
}

unsigned char getIndex(unsigned char ch, unsigned char index, unsigned char bitSize) {
    unsigned char result = 0;
    for (char i=0; i<bitSize; i++) {
        result |= (ch>>(index*bitSize+i) & 0x01)<<i;
    }

    return result;
}

// xiezhen@popcap.com.cn - 2012-08-15 - for parse bmp to pixdata
Image* GetBMPImage(const std::string& theFileName) {
#if FALSE
    FILE *fp;
    if ((fp = fopen(theFileName.c_str(), "rb")) == NULL)
        return NULL;
#else
	s3eFile *fp;
	if ((fp = s3eFileOpen(theFileName.c_str(), "rb")) == NULL)
		return NULL;
#endif
	BITMAP bmp;
	memset(&bmp.bmpHead, 0x0, sizeof(BITMAPFILEHEADER));

	//s3eFileSeek(fp, 0, S3E_FILESEEK_SET);
#if FALSE
    fread(&bmp.bmpHead, sizeof(BITMAPFILEHEADER), 1,fp);
    if (bmp.bmpHead.bfType != 0x4D42) {
        fclose( fp );												
        return NULL;
    }
    fread(&bmp.bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
#else
	s3eFileRead(&bmp.bmpHead, sizeof(BITMAPFILEHEADER), 1,fp);
	if (bmp.bmpHead.bfType != 0x4D42) {
		s3eFileClose( fp );												
		return NULL;
	}
	s3eFileRead(&bmp.bmpInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
#endif

    U32* aBits = new U32[bmp.bmpInfo.bmiHeader.biWidth*bmp.bmpInfo.bmiHeader.biHeight];
    U32* q = aBits;

    if (bmp.bmpInfo.bmiHeader.biBitCount > 8) {   
        U32 bmppicth = (((bmp.bmpInfo.bmiHeader.biWidth)*(bmp.bmpInfo.bmiHeader.biBitCount) + 31) >> 5) << 2;

        U8 *pEachLinBuf = (U8*)malloc(bmppicth);
        memset(pEachLinBuf, 0, bmppicth);
        U8 BytePerPix = (bmp.bmpInfo.bmiHeader.biBitCount) >> 3;
        U32 pitch = (bmp.bmpInfo.bmiHeader.biWidth) * BytePerPix;
        if(q && pEachLinBuf) {          
            for(short h=bmp.bmpInfo.bmiHeader.biHeight-1;h>=0;h--) {
#if FALSE
                fread(pEachLinBuf, bmppicth, 1, fp);
#else
                s3eFileRead(pEachLinBuf, bmppicth, 1, fp);
#endif
                q = aBits+bmp.bmpInfo.bmiHeader.biWidth*h;
                for(unsigned int w = 0;w < bmp.bmpInfo.bmiHeader.biWidth;w++) {
                    int r = pEachLinBuf[w*BytePerPix+2];
                    int g = pEachLinBuf[w*BytePerPix+1];
                    int b = pEachLinBuf[w*BytePerPix+0];

                    *q++ = MAKE_PIXEL( r, g, b, 0xff );
                }
            }
        }
        free(pEachLinBuf);
        pEachLinBuf = NULL;
    } else {
        unsigned short colorSize = 1;
        for (char i=0; i<bmp.bmpInfo.bmiHeader.biBitCount; i++) {
            colorSize *= 2;
        }
        RGBQUAD *colorTable = new RGBQUAD[colorSize];

        int pixelSize = bmp.bmpInfo.bmiHeader.biWidth*bmp.bmpInfo.bmiHeader.biHeight*bmp.bmpInfo.bmiHeader.biBitCount/8;
        U8 *pixelData = (U8*)malloc(pixelSize);
        U8 *pixelDataHead = pixelData;
#if FALSE
        fread(colorTable, colorSize*sizeof(RGBQUAD), 1, fp);
        fread(pixelData, pixelSize, 1, fp);
#else
        s3eFileRead(colorTable, colorSize*sizeof(RGBQUAD), 1, fp);
        s3eFileRead(pixelData, pixelSize, 1, fp);
#endif
        for(short h=bmp.bmpInfo.bmiHeader.biHeight-1; h>=0; h--) {
            q = aBits+bmp.bmpInfo.bmiHeader.biWidth*h;

            for(unsigned int w = 0; w<bmp.bmpInfo.bmiHeader.biWidth;) {
                unsigned char ch = *pixelData++;
                
                for (char i=0; i<8/bmp.bmpInfo.bmiHeader.biBitCount; i++) {
                    RGBQUAD rgbColor = colorTable[getIndex(ch, i, bmp.bmpInfo.bmiHeader.biBitCount)];
                    *q++ = MAKE_PIXEL(rgbColor.rgbRed, rgbColor.rgbGreen, rgbColor.rgbBlue, 0xff);
                    w++;
                }
            }
        }
        free(pixelDataHead);
        delete[] colorTable;
    }

	Image* anImage = new Image();
    anImage->mWidth = bmp.bmpInfo.bmiHeader.biWidth;
    anImage->mHeight = bmp.bmpInfo.bmiHeader.biHeight;
    anImage->mBits = (unsigned long*)aBits;
    

#if FALSE
    fclose(fp);
#else
	s3eFileClose(fp);
#endif
	return anImage;
}



//xiezhen@popcap.com.cn - 2012-8-27 - just differentiate png, jpg, bmp, gif. 
//ImageLib::IMAGE_TYPE GetImageType( const std::string& theFileName ) {
//#if FALSE
//    FILE *fp;
//    if ((fp = fopen(theFileName.c_str(), "rb")) == NULL)
//        return IMG_NULL;
//#else
//    if(!s3eFileCheckExists(theFileName.c_str())) {
//        return IMG_NULL;
//    }
//    s3eFile *fp;
//    if ((fp = s3eFileOpen(theFileName.c_str(), "rb")) == NULL)
//        return IMG_NULL;
//#endif
//
//    char cBuffer;
//#if FALSE
//    fread(&cBuffer, 1, 1, fp);
//#else
//    s3eFileRead(&cBuffer, 1, 1, fp);
//#endif
//    IMAGE_TYPE imgType = IMG_NULL;
//    if (cBuffer == 0x89) {
//        imgType = IMG_PNG;
//    } else if (cBuffer == 0x47) {
//        imgType = IMG_GIF;
//    } else if (cBuffer == 0x42) {
//        imgType = IMG_BMP;
//    } else if (cBuffer == 0xff) {
//        imgType = IMG_JPG;
//    }
//
//#if FALSE
//    fclose(fp);
//#else
//    s3eFileClose(fp);
//#endif
//    return imgType;
//}

size_t JPEG2000GetBytes( void *info, void *buffer, size_t count )
{
	FILE* fp = (FILE*)info;
	return fread( buffer, 1, count, fp );
}

void JPEG2000SkipBytes( void *info, size_t count )
{
	FILE* fp = (FILE*)info;
	fseek( fp, count, SEEK_CUR );
}

void JPEG2000Rewind( void *info )
{
	FILE* fp = (FILE*)info;
	fseek( fp, 0, SEEK_SET );
}

void JPEG2000ReleaseInfo( void *info )
{
	FILE* fp = (FILE*)info;
	fclose( fp );
}

Image* GetJPEG2000Image(const std::string& theFileName )
{
// dbanay TODO
#if 0
	OSErr error;
	Image* anImage = NULL;
	FILE *fp;


		if ((fp = fopen(theFileName.c_str(), "rb")) == NULL)
			return NULL;


/*
	FSMakeFSRefUnicode( theParentRef,<#UniCharCount nameLength#>,<#const UniChar * name#>,<#TextEncoding textEncodingHint#>,<#FSRef * newRef#>)
	
	FSSpec inFileSpec;
	FSCatalogInfoBitmap whichInfo = 0; // kFSCatInfoParentDirID;
	error = FSGetCatalogInfo( &fileRef, whichInfo, NULL, NULL, &inFileSpec, NULL );
	
	GraphicsImportComponent importComponent;
	::GetGraphicsImporterForFile( &inFileSpec, &importComponent );
	
	CGImageRef imageRef;
	UInt32 flags = kGraphicsImportCreateCGImageUsingCurrentSettings;
	ComponentResult result = GraphicsImportCreateCGImage( ci, &imageRef, flags );
*/	
	CGDataProviderCallbacks callbacks;
	callbacks.getBytes = &JPEG2000GetBytes;
	callbacks.skipBytes = &JPEG2000SkipBytes;
	callbacks.rewind = &JPEG2000Rewind;
	callbacks.releaseProvider = &JPEG2000ReleaseInfo;
	
	CGDataProviderRef dataProvider = CGDataProviderCreate( fp, &callbacks );

	if ( dataProvider )
	{
		CGImageRef imageRef = CGImageCreateWithJPEGDataProvider( dataProvider, NULL, false, kCGRenderingIntentDefault );
		if ( imageRef )
		{

			anImage = new Image();
			anImage->mWidth = CGImageGetWidth( imageRef );
			anImage->mHeight = CGImageGetHeight( imageRef );
			anImage->mBits = new unsigned long[ anImage->mWidth * anImage->mHeight ];
			
			CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName( kCGColorSpaceUserRGB );
			CGImageAlphaInfo info = /*kCGBitmapByteOrder32Little |*/ ( gIgnoreJPEG2000Alpha ? kCGImageAlphaNoneSkipFirst : kCGImageAlphaPremultipliedFirst );
			CGContextRef bitmapContext = CGBitmapContextCreate( (void*) anImage->mBits, anImage->mWidth, anImage->mHeight, 8, 4 * anImage->mWidth, colorSpace, info );
			CGColorSpaceRelease( colorSpace );
			if ( bitmapContext )
			{
				CGRect rect = CGRectMake( 0, 0, anImage->mWidth, anImage->mHeight );
				CGContextDrawImage( bitmapContext, rect, imageRef );
			
				CGContextRelease( bitmapContext );
			}

			CGImageRelease( imageRef );
		}
		CGDataProviderRelease( dataProvider );
	}
	return anImage;
#else
    return NULL;
#endif
}

int ImageLib::gAlphaComposeColor = 0xFFFFFF;
bool ImageLib::gAutoLoadAlpha = true;
bool ImageLib::gIgnoreJPEG2000Alpha = true;

void ImageLib::InitJPEG2000()
{
#ifdef _WIN32
	gJ2KCodec = ::LoadLibrary(_T("j2k-codec.dll"));
#endif
}

void ImageLib::CloseJPEG2000()
{
#ifdef _WIN32
	if (gJ2KCodec != NULL)
	{
		::FreeLibrary(gJ2KCodec);
		gJ2KCodec = NULL;
	}
#endif
}

void ImageLib::SetJ2KCodecKey(const std::string& theKey)
{
#ifdef _WIN32
	gJ2KCodecKey = theKey;
#endif
}


Image* ImageLib::GetImage(const std::string& theFilename, bool lookForAlphaImage )
{

#ifdef USE_TWIN_HEAPS
	printf("*** set heap 1\n");
	//s3eMemorySetInt(S3E_MEMORY_HEAP,1);
	MemoryDebug::GetInstance()->PushDualHeap();
#endif
	int aLastDotPos = theFilename.rfind('.');
	int aLastSlashPos = std::min(theFilename.rfind('\\'), theFilename.rfind('/'));

	std::string anExt;
	std::string aFilename;

	if (aLastDotPos > aLastSlashPos)
	{
		anExt = theFilename.substr(aLastDotPos, theFilename.length() - aLastDotPos);
		aFilename = theFilename.substr(0, aLastDotPos);
	}
	else
		aFilename = theFilename;

	Image* anImage = NULL;

//SJSJ changed priority order
	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".png") == 0) || (anExt.length() == 0)))
		 anImage = GetPNGImage(aFilename + ".png" );

	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".gif") == 0) || (anExt.length() == 0)))
		 anImage = GetGIFImage(aFilename + ".gif" );


	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".jpg") == 0) || (anExt.length() == 0)))
		 anImage = GetJPEGImage(aFilename + ".jpg" );

	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".jpeg") == 0) || (anExt.length() == 0)))
		anImage = GetJPEGImage(aFilename + ".jpeg" );

	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".bmp") == 0) || (anExt.length() == 0)))
		 anImage = GetBMPImage(aFilename + ".bmp" );

//SJSJ dont look foer what we havn't got..
//	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".tga") == 0) || (anExt.length() == 0)))
//		 anImage = GetTGAImage(aFilename + ".tga" );
//
//	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".pnx") == 0) || (anExt.length() == 0)))
//		 anImage = GetPNGImage(aFilename + ".pnx" );
//
//
//	if ((anImage == NULL) && ((stricmp(anExt.c_str(), ".jp2") == 0) || (anExt.length() == 0)))
//		 anImage = GetJPEG2000Image(aFilename + ".jp2" );

	// Check for alpha images
	Image* anAlphaImage = NULL;
	if(lookForAlphaImage)
	{
		// Check _ImageName
		anAlphaImage = GetImage(theFilename.substr(0, aLastSlashPos+1) + "_" +
			theFilename.substr(aLastSlashPos+1, theFilename.length() - aLastSlashPos - 1), false );

		// Check ImageName_
		if(anAlphaImage==NULL)
			anAlphaImage = GetImage(theFilename + "_", false );
	}



	// Compose alpha channel with image
	if (anAlphaImage != NULL) 
	{
		if (anImage != NULL)
		{
			if ((anImage->mWidth == anAlphaImage->mWidth) &&
				(anImage->mHeight == anAlphaImage->mHeight))
			{
				unsigned long* aBits1 = anImage->mBits;
				unsigned long* aBits2 = anAlphaImage->mBits;
				int aSize = anImage->mWidth*anImage->mHeight;

				for (int i = 0; i < aSize; i++)
				{
					*aBits1 = (*aBits1 & 0x00FFFFFF) | ((*aBits2 & 0xFF) << 24);
					++aBits1;
					++aBits2;
				}
			}

			delete anAlphaImage;
		}
		else if (gAlphaComposeColor==0xFFFFFF)
		{
			anImage = anAlphaImage;

			unsigned long* aBits1 = anImage->mBits;

			int aSize = anImage->mWidth*anImage->mHeight;
			for (int i = 0; i < aSize; i++)
			{
				*aBits1 = (0x00FFFFFF) | ((*aBits1 & 0xFF) << 24);
				++aBits1;
			}
		}
		else
		{
			const int aColor = gAlphaComposeColor;
			anImage = anAlphaImage;

			unsigned long* aBits1 = anImage->mBits;

			int aSize = anImage->mWidth*anImage->mHeight;
			for (int i = 0; i < aSize; i++)
			{
				*aBits1 = aColor | ((*aBits1 & 0xFF) << 24);
				++aBits1;
			}
		}
	}

#if (ASSOCIATED_ALPHA)
	// associate (pre-multiply) alpha.
	if ( anImage )
	{
		unsigned long* pixel = anImage->mBits;
		unsigned long* end = pixel + anImage->mWidth * anImage->mHeight;
		while ( pixel < end )
		{
			int a = (*pixel >> 24);
			int b = (*pixel >> 16 & 0xff) * a / 255;
			int g = (*pixel >>  8 & 0xff) * a / 255;
			int r = (*pixel       & 0xff) * a / 255;
			*pixel++ = ((a << 8 | b) << 8 | g) << 8 | r;
		}
	}
#endif
#ifdef USE_TWIN_HEAPS
	printf("*** set heap 0\n");
	//s3eMemorySetInt(S3E_MEMORY_HEAP,0);
	MemoryDebug::GetInstance()->PopDualHeap();
#endif
	return anImage;
}
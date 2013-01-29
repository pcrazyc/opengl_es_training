/*
 *  Common.h
 *
 *  Created by Dan Banay.
 *  Copyright 2007 PopCap Games. All rights reserved.
 *
 */

#ifndef __COMMON_H__
#define __COMMON_H__

 
#define MACOSX
#define MACOSX_TOUCH

#include "Platform.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <functional>
#include <wchar.h>
#include "ObjCHelpers.h"
#include "Constants.h"
#include "ModVal.h"

#ifdef I3D_OS_S3E
//not really sure how this is supposed to get included...
//(probably connected to the fact there are 2 common.h files and this is included in the other one)
#include "Win32Fakery.h"
using namespace Win32Emulation;
#endif

#define ASSOCIATED_ALPHA 1

double _wtof(
   const wchar_t *str 
);

wchar_t	*_wcstok(wchar_t * , const wchar_t *  );
int stricmp(const char *s,const char * t);
int wcsicmp(const wchar_t *s1, const wchar_t *s2);
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;


namespace Sexy
{




#ifdef _USE_WIDE_STRING
inline void sexystrtodbl(std::wstring& str,double &var)
{
	std::wistringstream instr(str);
	instr >> var;
}

inline void sexystrtoint(std::wstring& str,int &var)
{
	std::wistringstream instr(str);
	instr >> var;
}


typedef std::wstring			SexyString;
#define _S(x)				L ##x
#define sexytolower			towlower
#define sexytoupper         		towupper

#define sexystrncmp			wcsncmp
#define sexystrcmp			wcscmp
#define sexystricmp			wcsicmp
#define sexystrcoll			wcscoll
//#define sexysscanf			swscanf//sscanf
#define sexyatoi(s)			wcstol( (s), 0, 10 )
#define sexystrcpy			wcscpy
#define sexyvsscanf			vswscanf
#define sexyvfprintf			vfwprintf
#define sexyvsnprintf			vswprintf
#define sexystrtok			_wcstok
#define sexystrchr			wcschr
#define sexyisspace			iswspace
#define sexyatof			_wtof
#define sexystrlen			wcslen
#define sexystrcspn			wcscspn
#define sexystrspn			wcsspn

#define sexyisalnum			iswalnum

#define SexyStringToStringFast(x)	WStringToString(x)
#define SexyStringToWStringFast(x)	(x)
#define StringToSexyStringFast(x)	StringToWString(x)
#define WStringToSexyStringFast(x)	(x)

//#define sexystrtime			wcsftime
#define sexyprintf			wprintf

#else

inline void sexystrtodbl(std::string& astring,double &var)
{

	std::istringstream instr(astring);
	instr >> var;

}

inline void sexystrtoint(std::string& astring,int &var)
{

	std::istringstream instr(astring);
	instr >> var;

}

typedef std::string			SexyString;
#define _S(x)				x
#define sexytolower			tolower
#define sexytoupper         		toupper

#define sexystrncmp			strncmp
#define sexystrcmp			strcmp
#define sexystricmp			stricmp
#define sexystrcoll			strcoll
#define sexysscanf			sscanf
#define sexyatoi			atoi
#define sexystrcpy			strcpy
#define sexystrcspn			strcspn
#define sexystrspn			strspn
#define sexyvsscanf			vsscanf
#define sexyvfprintf			vfprintf
#define sexyvsnprintf			vsnprintf
#define sexystrlen          		strlen
#define sexystrtok			strtok
#define sexystrchr			strchr
#define sexyisspace         		isspace
#define sexyatof			atof

#define sexyisalnum			isalnum

#define SexyStringToStringFast(x)	(x)
#define SexyStringToWStringFast(x)	StringToWString(x)
#define StringToSexyStringFast(x)	(x)
#define WStringToSexyStringFast(x)	WStringToString(x)

#define sexystrtime			strftime
#define sexyprintf			printf

#endif

typedef SexyString::value_type					SexyChar;

const ulong			SEXY_RAND_MAX = 0x7FFFFFFF;
int					Rand();
int					Rand(int range);
float				Rand(float range);
void				SRand(ulong theSeed);


bool				StrPrefixNoCase(const SexyChar *theStr, const SexyChar *thePrefix, int maxLength = 10000000);
#ifdef _USE_WIDE_STRING
bool				StrPrefixNoCase(const char *theStr, const char *thePrefix, int maxLength = 10000000);
#endif
void SetCommaSeparator( SexyChar theSeparator );
SexyString			CommaSeperate(int theValue,int step=3);
SexyChar            *CommaSeperate_(int theValue);


#define LONG_BIGE_TO_NATIVE(l) (((l >> 24) & 0xFF) | ((l >> 8) & 0xFF00) | ((l << 8) & 0xFF0000) | ((l << 24) & 0xFF000000))
#define WORD_BIGE_TO_NATIVE(w) (((w >> 8) & 0xFF) | ((w << 8) & 0xFF00))
#define LONG_LITTLEE_TO_NATIVE(l) (l)
#define WORD_LITTLEE_TO_NATIVE(w) (w)

#define LENGTH(anyarray) (sizeof(anyarray) / sizeof(anyarray[0]))



inline void			inlineLTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
    theData.erase(0, theData.find_first_not_of(theChars));
}

inline void			inlineLTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
    theData.erase(0, theData.find_first_not_of(theChars));
}

inline void			inlineRTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
    theData.resize(theData.find_last_not_of(theChars) + 1);
}

inline void			inlineRTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
    theData.resize(theData.find_last_not_of(theChars) + 1);
}


inline void			inlineTrim(std::string &theData, const std::string& theChars = " \t\r\n")
{
	inlineRTrim(theData, theChars);
	inlineLTrim(theData, theChars);
}




inline void			inlineTrim(std::wstring &theData, const std::wstring& theChars = L" \t\r\n")
{
	inlineRTrim(theData, theChars);
	inlineLTrim(theData, theChars);
}


inline void			inlineUpper(std::string &theData)
{
	std::transform(theData.begin(), theData.end(), theData.begin(), toupper);
}

inline void			inlineLower(std::string &theData)
{
	std::transform(theData.begin(), theData.end(), theData.begin(), tolower);
}
	
unsigned short int	SexyCharToShort(const SexyChar&);
std::string			URLEncode(const std::string& theString);
std::string			StringToUpper(const std::string& theString);
std::wstring		StringToUpper(const std::wstring& theString);
std::string			StringToLower(const std::string& theString);
std::wstring		StringToLower(const std::wstring& theString);
std::wstring		StringToWString(const std::string &theString);
std::string			WStringToString(const std::wstring &theString);
SexyString			StringToSexyString(const std::string& theString);
SexyString			WStringToSexyString(const std::wstring& theString);
std::string			SexyStringToString(const SexyString& theString);
std::wstring		SexyStringToWString(const SexyString& theString);
std::string			Upper(const std::string& theData);
std::wstring		Upper(const std::wstring& theData);
std::string			Lower(const std::string& theData);
std::wstring		Lower(const std::wstring& theData);
std::string			Trim(const std::string& theString);
std::wstring		Trim(const std::wstring& theString);
std::string			ToString(const std::string& theString);
std::string			ToString(const std::wstring& theString);
std::wstring		ToWString(const std::string& theString);
std::wstring		ToWString(const std::wstring& theString);
SexyString			ToSexyString(const std::string& theString);
SexyString			ToSexyString(const std::wstring& theString);

bool				StringToInt(const std::string theString, int* theIntVal);
bool				StringToDouble(const std::string theString, double* theDoubleVal);
bool				StringToInt(const std::wstring theString, int* theIntVal);
bool				StringToDouble(const std::wstring theString, double* theDoubleVal);
std::string			XMLDecodeString(const std::string& theString);
std::string			XMLEncodeString(const std::string& theString);
std::wstring		XMLDecodeString(const std::wstring& theString);
std::wstring		XMLEncodeString(const std::wstring& theString);
std::string			GetFileName(const std::string& thePath, bool noExtension = false);
std::wstring		GetFileName(const std::wstring& thePath, bool noExtension = false);
std::string			GetFileDir(const std::string& thePath, bool withSlash = false);
std::wstring		GetFileDir(const std::wstring& thePath, bool withSlash = false);
std::string			GetFullPath(const std::string& theRelPath);
std::wstring		GetFullPath(const std::wstring& theRelPath);
std::string			GetPathFrom(const std::string& theRelPath, const std::string& theDir);
std::wstring		GetPathFrom(const std::wstring& theRelPath, const std::wstring& theDir);
std::string         GetCurDir();

std::string			RemoveTrailingSlash(const std::string& theDirectory);
std::string			AddTrailingSlash(const std::string& theDirectory);
time_t				GetFileDate(const std::string& theFileName);
void				Sleep(unsigned int inTime);
void                MkDir(const std::string& theDir);
bool				Deltree(const std::string& thePath);
bool				DeleteFile(const char* lpFileName);
std::string			GetAppDataFolder();
void				SetAppDataFolder( const std::string& thePath );

int					sexysscanf(const SexyChar* str,const SexyChar* format,...);
size_t				sexystrtime(SexyChar* str, size_t maxsize, const SexyChar* format, const struct tm *tp);

SexyString StrFormat(const SexyChar* fmt ...);

#ifdef _USE_WIDE_STRING
std::string StrFormat(const char* fmt ...);
#endif

struct StringLessNoCase { bool operator()(const std::string &s1, const std::string &s2) const { return stricmp(s1.c_str(),s2.c_str())<0; } };

// JPN - Added
struct StringLessNoCaseW { bool operator()(const std::wstring& s1, const std::wstring& s2) const { return wcsicmp(s1.c_str(),s2.c_str())<0; } };

struct StringEqualNoCase { bool operator()(const std::string& s1, const std::string& s2) const { return stricmp(s1.c_str(),s2.c_str())==0; } };
struct StringGreaterNoCase { bool operator()(const std::string& s1, const std::string& s2) const { return stricmp(s1.c_str(),s2.c_str())>0; } };

}

#endif

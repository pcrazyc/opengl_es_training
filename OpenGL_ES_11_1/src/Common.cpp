/*
 *  Common.cpp
 *
 *  Created by Dan Banay on 4/8/07.
 *
 */


#include "Common.h"
#include "MTRand.h"
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

static Sexy::SexyChar ForwardSlashChar = _S('/');
static Sexy::SexyChar BackwardSlashChar = _S('\\');
static Sexy::SexyChar CommaChar = _S(',');
static Sexy::SexyChar gFmtBuffer[2048];
static char gFmtBufferUTF8[2048];
static char gTempBufferUTF8[2048];
static char gArgBufferUTF8[2048];

double _wtof(
             const wchar_t *str 
)
{
    wchar_t *end;
    return wcstod(str, &end);
}

wchar_t	*_wcstok(wchar_t *str, const wchar_t *sep  )
{
    static wchar_t *ctx = NULL;
    return wcstok( str, sep, &ctx );
}

/* Compare lexigraphically two strings */
#ifndef I3D_OS_S3E
int  stricmp(const char *s1, const char *s2)
{
    char c1, c2;
    while (1)
    {
        c1 = tolower(*s1++);
        c2 = tolower(*s2++);
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
        if (c1 == 0) return 0;
    }
}
#endif


/* Compare lexigraphically two strings */
int  wcsicmp(const wchar_t *s1, const wchar_t *s2)
{
    wchar_t c1, c2;
    while (1)
    {
        c1 = towlower(*s1++);
        c2 = towlower(*s2++);
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
        if (c1 == 0) return 0;
    }
}


namespace Sexy
{
    
    static std::string gAppDataFolder = "boogers";
	
	MTRand gCommonMTRand;
    
    
    
    int Rand()
    {
        return gCommonMTRand.Next();
    }
    
    int Rand(int range)
    {
        return gCommonMTRand.Next((unsigned long)range);
    }
    
    float Rand(float range)
    {
        return gCommonMTRand.Next(range);
    }
    
    void SRand(ulong theSeed)
    {
        gCommonMTRand.SRand(theSeed);
    }
    
    struct CharToCharFunc
    {
        static const char* Str(const char* theStr)
        {
            return theStr;
        }
        
        static char Char(char theChar)
        {
            return theChar;
        }

		static char Char(wchar_t wchar)
		{
			char c;
			
			c= wchar & 0xff;
			return c;
		}

    };
    
    struct CharToWCharFunc
    {
        static const WCHAR* Str(const char* theStr)
        {
            return Sexy::StringToWString(theStr).c_str();
        }
        
        static WCHAR Char(char theChar)
        {
            return Sexy::StringToWString(std::string(1, theChar))[0];
        }
        static WCHAR Char(wchar_t theChar)
        {
            return theChar;
        }
    };
    
    
    
    
    
    
#ifdef _USE_WIDE_STRING
	int	sexysscanf(const SexyChar* str,const SexyChar* format,...)
	{
			int ans = 0;
			wcstombs((char*)(gFmtBufferUTF8),str,wcslen(str));
			wcstombs((char*)(gTempBufferUTF8),format,wcslen(format));

			va_list ap;
			va_start(ap, format );
			ans = sscanf((char*)(gFmtBufferUTF8), gTempBufferUTF8, ap);
			va_end(ap);

			return ans;

	}

	size_t	sexystrtime(SexyChar* str, size_t maxsize, const SexyChar* format, const struct tm *tp)
	{
		// Convert Format from Wide Char to UTF8
		size_t index = wcstombs((char*)(gFmtBufferUTF8),format,(int)(wcslen(format)));
		gFmtBufferUTF8[(int)index] = 0;
		index = strftime((char*)(gTempBufferUTF8), maxsize, gFmtBufferUTF8, tp);
		mbstowcs(str,gTempBufferUTF8,sizeof(gTempBufferUTF8));
		return index;
	}

	// Custom SPrintF implementation using SexyString operator+
	static SexyString SafeSPrintF(const SexyChar* fmt, va_list wide_ap)
	{
		SexyString outputString;
		
		SexyString		ssFmt(fmt);
		SexyChar		cmd;
		SexyChar*		fmt_it = (SexyChar*)fmt;
		int start_index	= 0;
		int end_index	= 1;
//		int index;
		SexyString arg, text;
		// Iterate through (null-terminated) format string
		for(;*fmt_it; fmt_it++, end_index++)
		{
			// Is specifier?
			if(*fmt_it == '%')
			{
				// Check if specifier is valid
				bool valid_tag = true;
				cmd = *(++fmt_it);
				end_index++;
				switch(cmd)
				{
				case 'c':
				case 'C':
					va_arg(wide_ap,SexyChar);
					printf("WARNING: Non-supported %%C detected on SafeSPrintF!");
					break;
				case 'd':
				case 'D':
				case 'i':
				case 'I':
				case 'u':
				case 'U':
					arg = CommaSeperate((int)va_arg(wide_ap,int),999);
					text = ssFmt.substr(start_index,end_index - start_index - 2);
					outputString = outputString + text + arg;	
					break;
				case 'f':
				case 'F':
					va_arg(wide_ap,float);
					printf("WARNING: Non-supported %%F detected on SafeSPrintF!");
					break;
				case 's':
				case 'S':
					arg = (SexyChar*)va_arg(wide_ap,SexyChar*);
					text = ssFmt.substr(start_index,end_index - start_index - 2);
					outputString = outputString + text + arg;	
					break;
				case '%':
					// Percentage, should write % into output
					// Remove 2nd % from string"
					text = ssFmt.substr(start_index,end_index - start_index - 1);
					outputString = outputString + text;	
					break;
				/************************************
				 * UNSUPPORTED SPECIFIERS
				 * e/E, g/G, o, x/X, p, n
				 * Any flags, width precision and length indicators not supported as well
				 * Any non-supported specifiers in input may result in corrupted output!
				 ************************************/
				default:
					valid_tag = false;
				}
				if(valid_tag)
					start_index = end_index;
			}
		}

		// Is there any text left to concatenate?
		end_index = ssFmt.size();
		if(start_index < end_index)
		{
			outputString = outputString + ssFmt.substr(start_index,end_index - start_index);
		}

		// Finished, Tada!
		return outputString;
	}
    
    SexyString StrFormat(const SexyChar* fmt ...)
    {
		va_list ap;
		va_start(ap, fmt);
		SexyString output = SafeSPrintF(fmt,ap);
		va_end(ap);

		return output;
    }
    
    std::string StrFormat(const char* fmt ...)
    {
        va_list ap;
        va_start(ap, fmt );
        vsprintf( (char *) gFmtBuffer, fmt, ap );
        va_end( ap );
        return (char *) gFmtBuffer;
    }
    
    
#else   
    SexyString StrFormat(const SexyChar* fmt ...)
    {
        va_list ap;
        va_start(ap, fmt );
        vsprintf( (char *) gFmtBuffer, fmt, ap );
        va_end( ap );
        return (char *) gFmtBuffer;
    }
    
    
    
#endif
    
    
void SetCommaSeparator( SexyChar theSeparator )
{
    CommaChar = theSeparator;
}

SexyChar *CommaSeperate_(int theValue,int step)
{
    static SexyChar buf[20];
    
    if( theValue < 0 )
	{
		// Match the desktop
		buf[0] = _S('\0');
		return buf;
	}
    
    SexyChar *p = &buf[ 19 ];
    int aPlace = 0;
    *p-- = _S('\0');
    do
    {
        if( aPlace == step )
        {
            *p-- = CommaChar;
            aPlace = 0;
        }
        *p-- = theValue % 10 + _S('0' );
        theValue /= 10;
        
        aPlace++;
        
    } while( theValue );
    
    return p+1;
    
}
SexyString CommaSeperate(int theValue,int step)

{    
    return CommaSeperate_( theValue, step );
}    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    bool StrPrefixNoCase(const SexyChar *theStr, const SexyChar *thePrefix, int maxLength)
    {
        int i;
        char c1 = 0, c2 = 0;
        for (i=0; i<maxLength; i++)
        {
            c1 = sexytolower(*theStr++);
            c2 = sexytolower(*thePrefix++);
            
            if (c1==0 || c2==0)
                break;
            
            if (c1!=c2)
                return false;
        }
        
        return c2==0 || i==maxLength;
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
#ifdef _USE_WIDE_STRING
    bool StrPrefixNoCase(const char *theStr, const char *thePrefix, int maxLength)
    {
        int i;
        char c1 = 0, c2 = 0;
        for (i=0; i<maxLength; i++)
        {
            c1 = tolower(*theStr++);
            c2 = tolower(*thePrefix++);
            
            if (c1==0 || c2==0)
                break;
            
            if (c1!=c2)
                return false;
        }
        
        return c2==0 || i==maxLength;
    }
    
	unsigned short SexyCharToShort(const SexyChar* aChar)
	{	
		
		return (unsigned short)(*aChar);
	}

#else

	unsigned short int SexyCharToShort(const SexyChar& aChar)
	{
		return (unsigned short)(unsigned char)(aChar);
	}
	

#endif
    
    
	std::string GetAppDataFolder()
	{
		return gAppDataFolder;
	}
    
    void SetAppDataFolder( const std::string& thePath )
	{
		gAppDataFolder = AddTrailingSlash( thePath );
	}
    
    std::string URLEncode(const std::string& theString)
    {
        const char* aHexChars = "0123456789ABCDEF";
        
        std::string aString;
        
        for (unsigned i = 0; i < theString.length(); i++)
        {
            switch (theString[i])
            {
                case ' ':
                    aString.insert(aString.end(), '+');
                    break;
                case '?':
                case '&':
                case '%':
                case '+':
                case '\r':
                case '\n':
                case '\t':
                    aString.insert(aString.end(), '%');
                    aString.insert(aString.end(), aHexChars[(theString[i] >> 4) & 0xF]);
                    aString.insert(aString.end(), aHexChars[(theString[i]     ) & 0xF]);
                    break;
                default:
                    aString.insert(aString.end(), theString[i]);
            }
        }
        
        return aString;
    }
    
    std::string StringToUpper(const std::string& theString)
    {
        std::string aString;
        
        for (unsigned i = 0; i < theString.length(); i++)
            aString += toupper(theString[i]);
        
        return aString;
    }
    
    std::wstring StringToUpper(const std::wstring& theString)
    {
        std::wstring aString;
        
        for (unsigned i = 0; i < theString.length(); i++)
            aString += towupper(theString[i]);
        
        return aString;
    }
    
    std::string StringToLower(const std::string& theString)
    {
        std::string aString;
        
        for (unsigned i = 0; i < theString.length(); i++)
            aString += tolower(theString[i]);
        
        return aString;
    }
    
    std::wstring StringToLower(const std::wstring& theString)
    {
        std::wstring aString;
        
        for (unsigned i = 0; i < theString.length(); ++i)
            aString += tolower(theString[i]);
        
        return aString;
    }
    
    std::wstring StringToWString(const std::string &theString)
    {
        std::wstring aString;
        aString.reserve(theString.length());
        for(size_t i = 0; i < theString.length(); ++i)
            aString += (unsigned char)theString[i];
        return aString;
    }
    
    std::string WStringToString(const std::wstring &theString)
    {
        size_t aRequiredLength = wcstombs( NULL, theString.c_str(), 0 );
        if (aRequiredLength < 256 )
        {
            static char aBuffer[256];
            wcstombs( aBuffer, theString.c_str(), 256 );
            return std::string(aBuffer);
        }
        else
        {
            //DBG_ASSERTE(aRequiredLength != (size_t)-1);
            if (aRequiredLength == (size_t)-1) return "";
            
            char* aBuffer = new char[aRequiredLength+1];
            wcstombs( aBuffer, theString.c_str(), aRequiredLength+1 );
            std::string aStr = aBuffer;
            delete[] aBuffer;
            return aStr;
        }
    }
    
    SexyString StringToSexyString(const std::string& theString)
    {
#ifdef _USE_WIDE_STRING
        return StringToWString(theString);
#else
        return SexyString(theString);
#endif
    }
    
    SexyString WStringToSexyString(const std::wstring &theString)
    {
#ifdef _USE_WIDE_STRING
        return SexyString(theString);
#else
        return WStringToString(theString);
#endif
    }
    
    std::string SexyStringToString(const SexyString& theString)
    {
#ifdef _USE_WIDE_STRING
        return WStringToString(theString);
#else
        return std::string(theString);
#endif
    }
    
    std::wstring SexyStringToWString(const SexyString& theString)
    {
#ifdef _USE_WIDE_STRING
        return std::wstring(theString);
#else
        return StringToWString(theString);
#endif
    }
    
    std::string Trim(const std::string& theString)
    {
        int aStartPos = 0;
        while ( aStartPos < (int) theString.length() && isspace(theString[aStartPos]) )
            aStartPos++;
        
        int anEndPos = theString.length() - 1;
        while ( anEndPos >= 0 && isspace(theString[anEndPos]) )
            anEndPos--;
        
        return theString.substr(aStartPos, anEndPos - aStartPos + 1);
    }
    
    std::wstring Trim(const std::wstring& theString)
    {
        int aStartPos = 0;
        while ( aStartPos < (int) theString.length() && iswspace(theString[aStartPos]) )
            aStartPos++;
        
        int anEndPos = theString.length() - 1;
        while ( anEndPos >= 0 && iswspace(theString[anEndPos]) )
            anEndPos--;
        
        return theString.substr(aStartPos, anEndPos - aStartPos + 1);
    }
    
    
    
    std::string XMLDecodeString(const std::string& theString)
    {
        std::string aNewString;
        
        
        for (ulong i = 0; i < theString.length(); i++)
        {
            char c = theString[i];
            
            if (c == '&')
            {
                int aSemiPos = theString.find(';', i);
                
                if (aSemiPos != -1)
                {
                    std::string anEntName = theString.substr(i+1, aSemiPos-i-1);
                    i = aSemiPos;
                    
                    if (anEntName == "lt")
                        c = '<';
                    else if (anEntName == "amp")
                        c = '&';
                    else if (anEntName == "gt")
                        c = '>';
                    else if (anEntName == "quot")
                        c = '"';
                    else if (anEntName == "apos")
                        c = '\'';
                    else if (anEntName == "nbsp")
                        c = ' ';
                    else if (anEntName == "cr")
                        c = '\n';
                }
            }				
            
            aNewString += c;
        }
        
        return aNewString;
    }
    
    std::wstring XMLDecodeString(const std::wstring& theString)
    {
        std::wstring aNewString;
        
        
        for (ulong i = 0; i < theString.length(); i++)
        {
            wchar_t c = theString[i];
            
            if (c == L'&')
            {
                int aSemiPos = theString.find(L';', i);
                
                if (aSemiPos != -1)
                {
                    std::wstring anEntName = theString.substr(i+1, aSemiPos-i-1);
                    i = aSemiPos;
                    
                    if (anEntName == L"lt")
                        c = L'<';
                    else if (anEntName == L"amp")
                        c = L'&';
                    else if (anEntName == L"gt")
                        c = L'>';
                    else if (anEntName == L"quot")
                        c = L'"';
                    else if (anEntName == L"apos")
                        c = L'\'';
                    else if (anEntName == L"nbsp")
                        c = L' ';
                    else if (anEntName == L"cr")
                        c = L'\n';
                }
            }				
            
            aNewString += c;
        }
        
        return aNewString;
    }
    
    
    std::string XMLEncodeString(const std::string& theString)
    {
        std::string aNewString;
        
        bool hasSpace = false;
        
        for (ulong i = 0; i < theString.length(); i++)
        {
            char c = theString[i];
            
            if (c == ' ')
            {
                if (hasSpace)
                {
                    aNewString += "&nbsp;";
                    continue;
                }
                
                hasSpace = true;
            }
            else
                hasSpace = false;
            
            /*if ((uchar) c >= 0x80)
             {
             // Convert to UTF
             aNewString += (char) (0xC0 | ((c >> 6) & 0xFF));
             aNewString += (char) (0x80 | (c & 0x3F));
             }
             else*/
            {		
                switch (c)
                {
                    case '<':
                        aNewString += "&lt;";
                        break;
                    case '&':		
                        aNewString += "&amp;";
                        break;
                    case '>':
                        aNewString += "&gt;";
                        break;
                    case '"':
                        aNewString += "&quot;";
                        break;
                    case '\'':
                        aNewString += "&apos;";
                        break;
                    case '\n':
                        aNewString += "&cr;";
                        break;
                    default:
                        aNewString += c;
                        break;
                }
            }
        }
        
        return aNewString;
    }
    
    std::wstring XMLEncodeString(const std::wstring& theString)
    {
        std::wstring aNewString;
        
        bool hasSpace = false;
        
        for (ulong i = 0; i < theString.length(); i++)
        {
            wchar_t c = theString[i];
            
            if (c == ' ')
            {
                if (hasSpace)
                {
                    aNewString += L"&nbsp;";
                    continue;
                }
                
                hasSpace = true;
            }
            else
                hasSpace = false;
            
            /*if ((uchar) c >= 0x80)
             {
             // Convert to UTF
             aNewString += (char) (0xC0 | ((c >> 6) & 0xFF));
             aNewString += (char) (0x80 | (c & 0x3F));
             }
             else*/
            {		
                switch (c)
                {
                    case L'<':
                        aNewString += L"&lt;";
                        break;
                    case L'&':		
                        aNewString += L"&amp;";
                        break;
                    case L'>':
                        aNewString += L"&gt;";
                        break;
                    case L'"':
                        aNewString += L"&quot;";
                        break;
                    case L'\'':
                        aNewString += L"&apos;";
                        break;
                    case L'\n':
                        aNewString += L"&cr;";
                        break;
                    default:
                        aNewString += c;
                        break;
                }
            }
        }
        
        return aNewString;
    }
    
    std::string Upper(const std::string& _data)
    {
        std::string s = _data;
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        return s;
    }
    
    std::wstring Upper(const std::wstring& _data)
    {
        std::wstring s = _data;
        std::transform(s.begin(), s.end(), s.begin(), towupper);
        return s;
    }
    
    std::string Lower(const std::string& _data)
    {
        std::string s = _data;
        std::transform(s.begin(), s.end(), s.begin(), tolower);
        return s;
    }
    
    std::wstring Lower(const std::wstring& _data)
    {
        std::wstring s = _data;
        std::transform(s.begin(), s.end(), s.begin(), towlower);
        return s;
    }
    
    
    bool StringToInt(const std::string theString, int* theIntVal)
    {
        *theIntVal = 0;
        
        if (theString.length() == 0)
            return false;
        
        int theRadix = 10;
        bool isNeg = false;
        
        unsigned i = 0;
        if (theString[i] == '-')
        {
            isNeg = true;
            i++;
        }
        
        for (; i < theString.length(); i++)
        {
            char aChar = theString[i];
            
            if ((theRadix == 10) && (aChar >= '0') && (aChar <= '9'))
                *theIntVal = (*theIntVal * 10) + (aChar - '0');
            else if ((theRadix == 0x10) && 
                     (((aChar >= '0') && (aChar <= '9')) || 
                      ((aChar >= 'A') && (aChar <= 'F')) || 
                      ((aChar >= 'a') && (aChar <= 'f'))))
            {			
                if (aChar <= '9')
                    *theIntVal = (*theIntVal * 0x10) + (aChar - '0');
                else if (aChar <= 'F')
                    *theIntVal = (*theIntVal * 0x10) + (aChar - 'A') + 0x0A;
                else
                    *theIntVal = (*theIntVal * 0x10) + (aChar - 'a') + 0x0A;
            }
            else if (((aChar == 'x') || (aChar == 'X')) && (i == 1) && (*theIntVal == 0))
            {
                theRadix = 0x10;
            }
            else
            {
                *theIntVal = 0;
                return false;
            }
        }
        
        if (isNeg)
            *theIntVal = -*theIntVal;
        
        return true;
    }
    
    bool StringToInt(const std::wstring theString, int* theIntVal)
    {
        *theIntVal = 0;
        
        if (theString.length() == 0)
            return false;
        
        int theRadix = 10;
        bool isNeg = false;
        
        unsigned i = 0;
        if (theString[i] == '-')
        {
            isNeg = true;
            i++;
        }
        
        for (; i < theString.length(); i++)
        {
            wchar_t aChar = theString[i];
            
            if ((theRadix == 10) && (aChar >= L'0') && (aChar <= L'9'))
                *theIntVal = (*theIntVal * 10) + (aChar - L'0');
            else if ((theRadix == 0x10) && 
                     (((aChar >= L'0') && (aChar <= L'9')) || 
                      ((aChar >= L'A') && (aChar <= L'F')) || 
                      ((aChar >= L'a') && (aChar <= L'f'))))
            {			
                if (aChar <= L'9')
                    *theIntVal = (*theIntVal * 0x10) + (aChar - L'0');
                else if (aChar <= L'F')
                    *theIntVal = (*theIntVal * 0x10) + (aChar - L'A') + 0x0A;
                else
                    *theIntVal = (*theIntVal * 0x10) + (aChar - L'a') + 0x0A;
            }
            else if (((aChar == L'x') || (aChar == L'X')) && (i == 1) && (*theIntVal == 0))
            {
                theRadix = 0x10;
            }
            else
            {
                *theIntVal = 0;
                return false;
            }
        }
        
        if (isNeg)
            *theIntVal = -*theIntVal;
        
        return true;
    }
    
    bool StringToDouble(const std::string theString, double* theDoubleVal)
    {
        *theDoubleVal = 0.0;
        
        if (theString.length() == 0)
            return false;
        
        bool isNeg = false;
        
        unsigned i = 0;
        if (theString[i] == '-')
        {
            isNeg = true;
            i++;
        }
        
        for (; i < theString.length(); i++)
        {
            char aChar = theString[i];
            
            if ((aChar >= '0') && (aChar <= '9'))
                *theDoubleVal = (*theDoubleVal * 10) + (aChar - '0');
            else if (aChar == '.')
            {
                i++;
                break;
            }
            else
            {
                *theDoubleVal = 0.0;
                return false;
            }
        }
        
        double aMult = 0.1;
        for (; i < theString.length(); i++)
        {
            char aChar = theString[i];
            
            if ((aChar >= '0') && (aChar <= '9'))
            {
                *theDoubleVal += (aChar - '0') * aMult;	
                aMult /= 10.0;
            }
            else
            {
                *theDoubleVal = 0.0;
                return false;
            }
        }
        
        if (isNeg)
            *theDoubleVal = -*theDoubleVal;
        
        return true;
    }
    
    bool StringToDouble(const std::wstring theString, double* theDoubleVal)
    {
        *theDoubleVal = 0.0;
        
        if (theString.length() == 0)
            return false;
        
        bool isNeg = false;
        
        unsigned i = 0;
        if (theString[i] == '-')
        {
            isNeg = true;
            i++;
        }
        
        for (; i < theString.length(); i++)
        {
            wchar_t aChar = theString[i];
            
            if ((aChar >= L'0') && (aChar <= L'9'))
                *theDoubleVal = (*theDoubleVal * 10) + (aChar - L'0');
            else if (aChar == L'.')
            {
                i++;
                break;
            }
            else
            {
                *theDoubleVal = 0.0;
                return false;
            }
        }
        
        double aMult = 0.1;
        for (; i < theString.length(); i++)
        {
            wchar_t aChar = theString[i];
            
            if ((aChar >= L'0') && (aChar <= L'9'))
            {
                *theDoubleVal += (aChar - L'0') * aMult;	
                aMult /= 10.0;
            }
            else
            {
                *theDoubleVal = 0.0;
                return false;
            }
        }
        
        if (isNeg)
            *theDoubleVal = -*theDoubleVal;
        
        return true;
    }
    
	template <class _T, class _Conv>
	static void FindLastSlashCharacter(const _T& thePath, int& pos)
	{
       pos = (int) thePath.rfind(_Conv::Char(ForwardSlashChar));
		if(pos == -1)
			pos = (int) thePath.rfind(_Conv::Char(BackwardSlashChar));
	}

	template <class _T, class _Conv>
	static typename _T::value_type FindAndGetLastSlashCharacter(const _T& thePath, int& pos)
	{
		typename _T::value_type slashChar = _Conv::Char(ForwardSlashChar);
        pos = (int) thePath.rfind(_Conv::Char(ForwardSlashChar));
		if(pos == -1)
		{
			pos = (int) thePath.rfind(_Conv::Char(BackwardSlashChar));
			if(pos != -1)	
				slashChar = _Conv::Char(BackwardSlashChar);
		}
		return slashChar;
	}

	template <class _T, class _Conv>
	static typename _T::value_type GetSlashCharacter(const _T& thePath)
	{
		int pos;
		return FindAndGetLastSlashCharacter<_T,_Conv>(thePath, pos);
	}

    template <class _T, class _Conv>
    static _T GetFileName_(const _T& thePath, bool noExtension)
    {
        int aLastSlash;
		
		FindLastSlashCharacter<_T,_Conv>(thePath, aLastSlash);
        
        if (noExtension)
        {
            int aLastDot = (int)thePath.rfind(_Conv::Char('.'));
            if (aLastDot > aLastSlash)
                return thePath.substr(aLastSlash + 1, aLastDot - aLastSlash - 1);
        }
        
        if (aLastSlash == -1)
            return thePath;
        else
            return thePath.substr(aLastSlash + 1);
    }
    
    std::string GetFileName(const std::string& thePath, bool noExtension)
    {
        return GetFileName_<std::string, CharToCharFunc>(thePath, noExtension);
    }
    
    std::wstring GetFileName(const std::wstring& thePath, bool noExtension)
    {
        return GetFileName_<std::wstring, CharToWCharFunc>(thePath, noExtension);
    }
    
    template <class _T, class _Conv>
    static _T GetFileDir_(const _T& thePath, bool withSlash)
    {
        int aLastSlash;
		FindLastSlashCharacter<_T,_Conv>(thePath, aLastSlash);
        
		if (aLastSlash == -1)
            return _Conv::Str("");
        else
        {
            if (withSlash)
                return thePath.substr(0, aLastSlash+1);
            else
                return thePath.substr(0, aLastSlash);
        }
    }
    
    std::string GetFileDir(const std::string& thePath, bool withSlash)
    {
        return GetFileDir_<std::string, CharToCharFunc>(thePath, withSlash);
    }
    
    std::wstring GetFileDir(const std::wstring& thePath, bool withSlash)
    {
        return GetFileDir_<std::wstring, CharToWCharFunc>(thePath, withSlash);
    }
    
    
    std::string RemoveTrailingSlash(const std::string& theDirectory)
    {
        int aLen = theDirectory.length();
		std::string::value_type SlashChar = GetSlashCharacter<std::string,CharToCharFunc>(theDirectory);

        if ((aLen > 0) && (theDirectory[aLen-1] == SlashChar))
            return theDirectory.substr(0, aLen - 1);
        else
            return theDirectory;
    }
    
    std::string	AddTrailingSlash(const std::string& theDirectory)
    {
		std::string::value_type SlashChar = GetSlashCharacter<std::string,CharToCharFunc>(theDirectory);

        if (!theDirectory.empty())
        {
            char aChar = theDirectory[theDirectory.length()-1];
            if (aChar!=SlashChar)
                return theDirectory + SlashChar;
            else
                return theDirectory;
        }
        else
            return "";
    }
    
    time_t GetFileDate(const std::string& theFileName)
    {
        time_t aFileDate = 0;
        
        struct stat aFileStat;
        if (stat(theFileName.c_str(), &aFileStat) == 0)
            aFileDate = aFileStat.st_mtime;
        
        return aFileDate;
    }
    
    void Sleep(unsigned int inTime)
    {
        struct timespec timeOut,remains;
        if( inTime >= 1000 )
        {
            sleep( inTime / 1000 );
            inTime = inTime % 1000;
        }
        
        timeOut.tv_sec = 0;
        timeOut.tv_nsec = 1000000 * inTime; // milliseconds to nanoseconds
        
        nanosleep(&timeOut, &remains); 
    }
    
    void MkDir(const std::string& theDir)
    {
		std::string::value_type SlashChar = GetSlashCharacter<std::string,CharToCharFunc>(theDir);
        std::string aPath = theDir;

        int aCurPos = 0;
        for (;;)
        {
            int aSlashPos = aPath.find(SlashChar, aCurPos);
            if (aSlashPos == -1)
            {
				// Webster added. I found it will make an assert when the path is empty.
			//	if(strstr(aPath.c_str(), "")) 
				if(strcmp(aPath.c_str(), "") == 0) 
					break;

                mkdir(aPath.c_str(), 0x3ED);
                break;
            }
            
            aCurPos = aSlashPos+1;
            
            std::string aCurPath = aPath.substr(0, aSlashPos);
            mkdir(aCurPath.c_str(), 0x3ED);
        }
    }
    
	bool Deltree(const std::string& thePath)
	{
		bool success = true;
		
		std::string aSourceDir = AddTrailingSlash( thePath );
		
		if (aSourceDir.length() < 3)
			return false;
		
		DIR* aDir = opendir(aSourceDir.c_str());
		if (aDir == NULL)
			return false;
		
		struct dirent* aDirEnt;
		while ((aDirEnt = readdir(aDir)) != NULL)
		{
			struct stat aFileStat;
			if (strcmp(aDirEnt->d_name, ".") != 0 &&
				strcmp(aDirEnt->d_name, "..") != 0)
			{
				if (stat(aDirEnt->d_name, &aFileStat) == 0)
				{
					if (S_ISDIR(aFileStat.st_mode) && !S_ISLNK(aFileStat.st_mode))
					{
						if (!Deltree(aSourceDir + aDirEnt->d_name))
							success = false;
					}
					else if (unlink((aSourceDir + aDirEnt->d_name).c_str()) != 0)
						success = false;
				}
			}
		}
		closedir(aDir);
		
		if (rmdir(thePath.c_str()) == 0)
			success = false;
		
		return success;
	}
	
    bool DeleteFile(const char* lpFileName)
    {
        int result = remove( lpFileName );
        return (0 == result || errno == ENOENT);
    }
    
    
    
    std::string GetFullPath(const std::string& theRelPath)
    {
        return GetPathFrom(theRelPath, GetCurDir());
    }

    
    template <class _T, class _Conv>
    static _T GetPathFrom_(const _T& theRelPath, const _T& theDir)
    {
		typename _T::value_type aSlashChar = GetSlashCharacter<_T,_Conv>(theDir);

        _T aDriveString;
        _T aNewPath = theDir;
        
        if ((theRelPath.length() >= 2) && (theRelPath[1] == _Conv::Char(':')))
            return theRelPath;
        
        //typename _T::value_type aSlashChar = _Conv::Char(SlashChar);
        
        if ((aNewPath.length() >= 2) && (aNewPath[1] == ':'))
        {
            aDriveString = aNewPath.substr(0, 2);
            aNewPath.erase(aNewPath.begin(), aNewPath.begin()+2);
        }
        
        // Append a trailing slash if necessary
        if ((aNewPath.length() > 0) && (aNewPath[aNewPath.length()-1] != aSlashChar))
            aNewPath += aSlashChar;
        
        _T aTempRelPath = theRelPath;
        
        for (;;)
        {
            if (aNewPath.length() == 0)
                break;
            
            int aFirstSlash = aTempRelPath.find(aSlashChar);
            
            if (aFirstSlash == -1)
                break;
            
            _T aChDir = aTempRelPath.substr(0, aFirstSlash);
            
            aTempRelPath.erase(aTempRelPath.begin(), aTempRelPath.begin() + aFirstSlash + 1);						
            
            if (aChDir.compare(_Conv::Str("..")) == 0)
            {			
                int aLastDirStart = aNewPath.length() - 1;
                while ((aLastDirStart > 0) && (aNewPath[aLastDirStart-1] != aSlashChar))
                    aLastDirStart--;
                
                _T aLastDir = aNewPath.substr(aLastDirStart, aNewPath.length() - aLastDirStart - 1);
                if (aLastDir.compare(_Conv::Str("..")) == 0)
                {
                    aNewPath += _Conv::Str("..");
                    aNewPath += aSlashChar;
                }
                else
                {
                    aNewPath.erase(aNewPath.begin() + aLastDirStart, aNewPath.end());
                }
            }		
            else if (aChDir.compare(_Conv::Str("")) == 0)
            {
                aNewPath = aSlashChar;
                break;
            }
            else if (aChDir.compare(_Conv::Str(".")) != 0)
            {
                aNewPath += aChDir + aSlashChar;
                break;
            }
        }
        
        aNewPath = aDriveString + aNewPath + aTempRelPath;
        
        return aNewPath;
    }
    
    
    std::string GetCurDir()
    {
        char aDir[256];
        return getcwd(aDir, sizeof(aDir));
    }
    
    
    std::string GetPathFrom(const std::string& theRelPath, const std::string& theDir)
    {
        return GetPathFrom_<std::string, CharToCharFunc>(theRelPath, theDir);
    }
    
    std::wstring GetPathFrom(const std::wstring& theRelPath, const std::wstring& theDir)
    {
        return GetPathFrom_<std::wstring, CharToWCharFunc>(theRelPath, theDir);
    }
    
    
    std::string ToString(const std::string& theString)
    {
        return theString;
    }
    
    std::string ToString(const std::wstring& theString)
    {
        return WStringToString(theString);
    }
    
    std::wstring ToWString(const std::string& theString)
    {
        return StringToWString(theString);
    }
    
    std::wstring ToWString(const std::wstring& theString)
    {
        return theString;
    }
    
    SexyString ToSexyString(const std::string& theString)
    {
        return StringToSexyString(theString);
    }
    
    SexyString ToSexyString(const std::wstring& theString)
    {
        return WStringToSexyString(theString);
    }
    
    
    
}


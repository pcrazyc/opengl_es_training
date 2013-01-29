// byteswap.h : Byte Swap 
/////////////////////////////////////////////////////////////////////////////
//
// By Darren Walker
//
// (c) Copyright 2002, United Developers, LLC, All Rights Reserved
//
// This software is the property of United Developers, LLC, and is legally
// protected as a trade secret, proprietary information, and copyrighted work
// of United Developers, LLC. It may not be used, duplicated, or disclosed to
// others outside of United Developers, LLC, nor may it be modified, translated,
// etc., except as specifically permitted by the software license terms or an
// agreement with United Developers, LLC.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _byteswap_h
#define _byteswap_h

/////////////////////////////////////////////////////////////////////////////
// Byte Swapping Routines
//
// ByteSwap() returns the swapped value (regardless of platform)
// SwapBytes() swaps the bytes in place (regardless of platform)
// FixBytes() only swaps the bytes if the current platform is different from
//   the base platform (Currently, the base platform is little endian).
/////////////////////////////////////////////////////////////////////////////
inline unsigned short ByteSwap(unsigned short inValue)   {return ( unsigned short ) ( (inValue << 8) | (inValue >> 8) );}
inline short          ByteSwap(signed short inValue)     {return (signed short) ByteSwap((unsigned short) inValue);}
inline unsigned int   ByteSwap(unsigned int inValue)     {return (((unsigned int) ByteSwap((unsigned short) inValue)) << 16) | (unsigned int) ByteSwap((unsigned short) (inValue >> 16));}
inline int            ByteSwap(signed int inValue)       {return (signed int) ByteSwap((unsigned int) inValue);}
inline unsigned long  ByteSwap(unsigned long inValue)    {return (unsigned long) ByteSwap((unsigned int) inValue);}
inline long           ByteSwap(signed long inValue)      {return (signed long) ByteSwap((unsigned int) inValue);}
inline unsigned long long  ByteSwap(unsigned long long inValue)    {return (((unsigned long long) ByteSwap((unsigned long) inValue)) << 32) | (unsigned long long) ByteSwap((unsigned long) (inValue >> 32));}
inline long long           ByteSwap(signed long long inValue)      {return (signed long long) ByteSwap((unsigned long long) inValue);}
inline unsigned char  ByteSwap(unsigned char inValue)    {return inValue;}
inline char           ByteSwap(signed char inValue)      {return inValue;}
inline float          ByteSwap(float inValue)            {
															unsigned long tempLong = *(unsigned long*)(void*)&(inValue); 
															unsigned long tempLong1 = ByteSwap(tempLong);
															float tempDouble = *(float*)(void*)&tempLong1;
															return tempDouble;
														 }

inline double         ByteSwap(double inValue)           {
															unsigned long long tempLong = *(unsigned long long*)(void*)&(inValue); 
															unsigned long long tempLong1 = ByteSwap(tempLong);
															double tempDouble = *(double*)(void*)&tempLong1;
															return tempDouble;
														 }

inline void	SwapBytes(unsigned short& ioValue)  {ioValue = ByteSwap(ioValue);}
inline void	SwapBytes(signed short& ioValue)    {SwapBytes((unsigned short&) ioValue);}
inline void	SwapBytes(unsigned int& ioValue)    {ioValue = ByteSwap(ioValue);}
inline void	SwapBytes(signed int& ioValue)      {SwapBytes((unsigned int&) ioValue);}
inline void	SwapBytes(unsigned long& ioValue)   {SwapBytes((unsigned int&) ioValue);}
inline void	SwapBytes(signed long& ioValue)     {SwapBytes((unsigned int&) ioValue);}
inline void	SwapBytes(unsigned long long& ioValue)   {ioValue = ByteSwap((unsigned long long&) ioValue);}
inline void	SwapBytes(signed long long& ioValue)     {SwapBytes((unsigned long long&) ioValue);}
inline void	SwapBytes(unsigned char& ioValue)   {/*nothing to do*/}
inline void	SwapBytes(signed char& ioValue)     {/*nothing to do*/}
inline void	SwapBytes(char& ioValue)			{/*nothing to do*/}
inline void	SwapBytes(float& ioValue)           {
													unsigned long tempLong = *(unsigned long*)(void*)&(ioValue); 
													SwapBytes(tempLong);
													ioValue = *(float*)(void*)&tempLong;
												}
inline void	SwapBytes(double& ioValue)			{
													unsigned long long tempLong = *(unsigned long long*)(void*)&(ioValue); 
													SwapBytes(tempLong);
													ioValue = *(double*)(void*)&tempLong;
												}


#ifdef PLATFORM_BIG_ENDIAN
inline void	FixBytes(unsigned short& ioValue)   {SwapBytes(ioValue);}
inline void	FixBytes(signed short& ioValue)     {SwapBytes(ioValue);}
inline void	FixBytes(unsigned int& ioValue)     {SwapBytes(ioValue);}
inline void	FixBytes(signed int& ioValue)       {SwapBytes(ioValue);}
inline void	FixBytes(unsigned long& ioValue)    {SwapBytes(ioValue);}
inline void	FixBytes(signed long& ioValue)      {SwapBytes(ioValue);}
inline void	FixBytes(unsigned char& ioValue)    {SwapBytes(ioValue);}
inline void	FixBytes(signed char& ioValue)      {SwapBytes(ioValue);}
inline void	FixBytes(char& ioValue)				{SwapBytes(ioValue);}
inline void	FixBytes(float& ioValue)            {SwapBytes(ioValue);}
inline void	FixBytes(double& ioValue)           {SwapBytes(ioValue);}
#else
inline void	FixBytes(signed short& ioValue)     {}
inline void	FixBytes(unsigned short& ioValue)   {}
inline void	FixBytes(signed int& ioValue)       {}
inline void	FixBytes(unsigned int& ioValue)     {}
inline void	FixBytes(signed long& ioValue)      {}
inline void	FixBytes(unsigned long& ioValue)    {}
inline void	FixBytes(signed char& ioValue)      {}
inline void	FixBytes(char& ioValue)				{}
inline void	FixBytes(unsigned char& ioValue)    {}
inline void	FixBytes(float& ioValue)            {}
inline void	FixBytes(double& ioValue)           {}
#endif

#endif //_byteswap_h

#pragma once

#include <IwGL.h>
#include "GLES/gl.h"
#include <math.h>

class Vertex3D {
public:
    Vertex3D(float x=0, float y=0, float z=0, float w=1.0f);
    static Vertex3D Vertex3DMake(float x, float y, float z, float w=1.0f);
public:
    float x;
    float y;
    float z;
    float w;
};

class Color3D {
public:
    Color3D(float r=0, float g=0, float b=0, float a=1.0f);
    static Color3D Color3DMake(float r, float g, float b, float a=1.0f);
public:
    float r;
    float g;
    float b;
    float a;
};

class Matrix3D {
public:
    static Matrix3D unitMatrix3D;

    Matrix3D();
    Matrix3D(float m[], int n=16);

    Matrix3D& operator + (const Matrix3D &matrix);
    Matrix3D& operator * (const Matrix3D &matrix);

    void Rotate(float angle, const Vertex3D &direction);
public:
    float mMatrixData[16];
};

class FVector3  
{  
public:  
	union  
	{  
		struct  
		{  
			float X, Y, Z;  
		};  
		struct  
		{  
			float x, y, z;  
		};  
		float v[3];  
	};  
public:  
	FVector3(){}  
	FVector3(float x1,float y1,float z1):x(x1),y(y1),z(z1)  
	{}  
	FVector3(const FVector3& InV);  

	FVector3 operator^(const FVector3& V) const;  
	FVector3& Normalize();  

};  

inline  
FVector3::FVector3(const FVector3& InV)  
{  
	x = InV.x;  
	y = InV.y;  
	z = InV.z;  
}  

inline float appInvSqrt(float f) { return (float)(1.f/sqrt(f)); }  

inline FVector3&  
FVector3::Normalize()  
{  
	float SquareSum = X*X + Y*Y + Z*Z;  
	if( SquareSum < 0.000001 )  
		return *this;  
	float Scale = appInvSqrt(SquareSum);  
	X *= Scale;  
	Y *= Scale;  
	Z *= Scale;  
	return *this;  
}  

inline FVector3   
FVector3::operator^( const FVector3& V ) const  
{  
	return FVector3(Y * V.Z - Z * V.Y, Z * V.X - X * V.Z, X * V.Y - Y * V.X );  
}  


static void suLookAt(float eyeX,float eyeY,float eyeZ,float centerX,float centerY,float centerZ,float upX,float upY,float upZ)  
{  
	float directMat[16];  

	for (int i = 0 ;i<16;i++)  
	{  
		directMat[i] = 0;  
	}  

	directMat[15]= 1;  
	FVector3 fvDirect(centerX-eyeX,centerY-eyeY,centerZ-eyeZ);  
	fvDirect.Normalize();  
	FVector3 fvUpD(upX,upY,upZ);  
	fvUpD.Normalize();  
	FVector3 fvC = fvDirect^fvUpD;  
	fvC.Normalize();  

	FVector3 fvUp = fvC^fvDirect;  
	fvUp.Normalize();  

	fvDirect.x = -fvDirect.x;  
	fvDirect.y = -fvDirect.y;  
	fvDirect.z = -fvDirect.z;  

	directMat[0] = fvC.x;  
	directMat[4] = fvC.y;  
	directMat[8] = fvC.z;  
	directMat[1] = fvUp.x;  
	directMat[5] = fvUp.y;  
	directMat[9] = fvUp.z;  
	directMat[2] = fvDirect.x;  
	directMat[6] = fvDirect.y;  
	directMat[10] = fvDirect.z;  

	glLoadMatrixf(directMat);  

	glTranslatef(-eyeX,-eyeY,-eyeZ);  
}  

//void texcoord(float& v0,float& v1, float& v2, float &x, float &y);
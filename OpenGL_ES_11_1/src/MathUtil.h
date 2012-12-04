#pragma once

class Vertex3D {
    Vertex3D(float x=0, float y=0, float z=0, float w=1.0f);
    static Vertex3D Vertex3DMake(float x, float y, float z, float w=1.0f);
public:
    float x;
    float y;
    float z;
    float w;
};

class Color3D {
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
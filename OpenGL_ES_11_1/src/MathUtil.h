#pragma once

class Vertex {
    Vertex(float x, float y, float z, float w=1.0f);
public:
    float x;
    float y;
    float z;
    float w;
};

class Color {
    Color(float r, float g, float b, float a=1.0f);
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

    void Rotate(float angle, const Vertex &direction);
public:
    float mMatrixData[16];

    
};
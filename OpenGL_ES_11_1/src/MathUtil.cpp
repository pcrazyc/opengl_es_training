#include "MathUtil.h"
#include "math.h"

Vertex3D::Vertex3D( float x, float y, float z, float w ) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vertex3D Vertex3D::Vertex3DMake( float x, float y, float z, float w ) {
    return Vertex3D(x, y, z, w);
}


Color3D::Color3D( float r, float g, float b, float a/*=1.0f*/ ) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Color3D Color3D::Color3DMake( float r, float g, float b, float a/*=1.0f*/ ) {
    return Color3D(r, g, b, a);
}

Matrix3D::Matrix3D( float m[], int n/*=16*/ ) {
    if (n != 16) {
        //TODO ASSERT
        return;
    }

    for (int i=0; i<n; i++)  {
        mMatrixData[i] = m[i];
    }
}

Matrix3D::Matrix3D() {
    for (int i=0; i<4; i++)
        for (int j=0; j<4; j++) 
            mMatrixData[i*4+j] = float(i==j);
}

void Matrix3D::Rotate( float angle, const Vertex3D &direction ) {
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float m[16] = {
        cosAngle+(1-cosAngle)*direction.x*direction.x, (1-cosAngle)*direction.x*direction.y-sinAngle*direction.z, (1-cosAngle)*direction.x*direction.z+sinAngle*direction.y, 0,
        (1-cosAngle)*direction.x*direction.y+sinAngle*direction.z, cosAngle+(1-cosAngle)*direction.y*direction.y, (1-cosAngle)*direction.y*direction.z-sinAngle*direction.x, 0,
        (1-cosAngle)*direction.x*direction.z-sinAngle*direction.y, (1-cosAngle)*direction.y*direction.z+sinAngle*direction.x, cosAngle+(1-cosAngle)*direction.z*direction.z, 0,
        0, 0, 0, 1.0f
    };

    const Matrix3D matrixRotate(m);
    *this = *this * matrixRotate;
}

Matrix3D& Matrix3D::operator+( const Matrix3D &matrix ) {
    for (int i=0; i<16; i++) {
        mMatrixData[i] = mMatrixData[i] + matrix.mMatrixData[i];
    }

    return *this;
}

Matrix3D& Matrix3D::operator*( const Matrix3D &matrix ) {
    float m[16];
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            m[i*4+j] = 0;
            for (int k=0; k<4; k++) {
                m[i*4+j] += mMatrixData[i*4+k]*matrix.mMatrixData[k*4+j];
            }
        }
    }

    for (int i=0; i<16; i++) {
        mMatrixData[i] = m[i];
    }

    return *this;
}

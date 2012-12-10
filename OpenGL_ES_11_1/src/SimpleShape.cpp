#include "SimpleShape.h"

SimpleShape::SimpleShape() {
    mVertices = NULL;
    mColors = NULL;
    mIndices = NULL;
}

SimpleShape::SimpleShape( const float *vertices, const GLubyte *indices, const float *colors/*=NULL*/ ) {
    mVertices = vertices;
    mColors = colors;
    mIndices = indices;
}

void SimpleShape::Draw() {
    if (mVertices == NULL || mIndices == NULL) return;

	Shape::Draw();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, mColors);
    glVertexPointer(3, GL_FLOAT, 0, mVertices);
    glDrawElements(GL_TRIANGLES, sizeof(mIndices)/sizeof(GLubyte), GL_UNSIGNED_BYTE, mIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
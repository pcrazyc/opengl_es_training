#pragma once

#include "IwGL.h"
#include "s3e.h"

class ShaderUtil {
public:
    static ShaderUtil* SharedShaderUtil();
    static void PurgeShaderUtil();

    GLuint LoadShader(GLenum shaderType, const char* pSource);
    GLuint LoadShaderFromFile(GLenum shaderType, const char* pFileName);

    GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);
    bool CheckGLError(const char* output = "");
private:
    static ShaderUtil *pSharedShaderUtil;
};
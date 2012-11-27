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
    GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
    GLuint CreateProgramFromFile(const char* pVertexFile, const char* pFragmentFile);
    bool CheckGLError(const char* output = "");
private:
    static ShaderUtil *pSharedShaderUtil;
};
#include "ShaderUtil.h"
#include <fstream>
#include <sstream>

ShaderUtil* ShaderUtil::pSharedShaderUtil = 0;

ShaderUtil* ShaderUtil::SharedShaderUtil() {
    if (!pSharedShaderUtil) {
        pSharedShaderUtil = new ShaderUtil();
    }

    return pSharedShaderUtil;
}

void ShaderUtil::PurgeShaderUtil() {
    if (!pSharedShaderUtil) return;

    delete pSharedShaderUtil;
    pSharedShaderUtil = 0;    
}

GLuint ShaderUtil::LoadShader( GLenum shaderType, const char* pSource ) {
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
    }
    
    return shader;
}

GLuint ShaderUtil::LoadShaderFromFile( GLenum shaderType, const char* pFileName ) {
    std::ifstream file;
    file.open(pFileName);

    if (!file) return 0;

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();

    return LoadShader(shaderType, stream.str().c_str());
}

GLuint ShaderUtil::CreateProgram( const char* pVertexSource, const char* pFragmentSource ) {
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, pVertexSource);
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, pFragmentSource);

    return CreateProgram(vertexShader, fragmentShader);
}

GLuint ShaderUtil::CreateProgram( GLuint vertexShader, GLuint fragmentShader ) {
    if (vertexShader == 0 || fragmentShader == 0) return 0;

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    return shaderProgram;
}

bool ShaderUtil::CheckGLError( const char* output ) {
    int error;
    bool bError = true;
    while ((error = glGetError()) != GL_NO_ERROR) {
        printf("ES20_ERROR(%s): glError: %d", output, error);
        bError = false;
    }

    return bError;
}

GLuint ShaderUtil::CreateProgramFromFile( const char* pVertexFile, const char* pFragmentFile ) {
    GLuint vertexShader = LoadShaderFromFile(GL_VERTEX_SHADER, pVertexFile);
    GLuint fragmentShader = LoadShaderFromFile(GL_FRAGMENT_SHADER, pFragmentFile);

    return CreateProgram(vertexShader, fragmentShader);
}

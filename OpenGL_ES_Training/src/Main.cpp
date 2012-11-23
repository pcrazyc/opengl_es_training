// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"
#include "ShaderUtil.h"
#include <math.h>

// Standard C-style entry point. This can take args if required.

const char* vertexSrc = "attribute vec4 position; uniform highp mat4 mat; varying mediump vec2 pos; void main() { gl_Position = position * mat; pos = position.xy; }";
const char* fragmentSrc = "varying mediump vec2 pos; uniform mediump float phase; void main() { gl_FragColor = vec4(1, 1, 1, 1) * sin((pos.x * pos.x + pos.y * pos.y) * 40.0 + phase); }";

int main()
{
    IwGLInit();
    GLenum shaderProgram = ShaderUtil::SharedShaderUtil()->CreateProgram(vertexSrc, fragmentSrc);
    glUseProgram(shaderProgram);
    float offset = 0;
    // Loop forever, until the user or the OS performs some action to quit the app
    while(!s3eDeviceCheckQuitRequest()
          && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
          && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
          )
    {
        // Clear the surface
        int w = IwGLGetInt(IW_GL_WIDTH);
        int h = IwGLGetInt(IW_GL_HEIGHT);

        glViewport(0, 0, w, h) ;
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float angle = IwGLGetInt(IW_GL_ROTATE) * 3.141f / 2;
        float m[16] = { cosf(angle), sinf(angle), 0, 0,
            -sinf(angle), cosf(angle), 0, 0,
            0, 0, 1.0f, 0,
            0, 0, 0, 1.0f};

        glUniform1f(glGetUniformLocation(shaderProgram, "phase"), offset);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mat"), 1, GL_FALSE, m);

        GLfloat vVertices[] = {0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f};
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        offset = fmodf(offset + 0.2f, 2*3.141f);

        IwGLSwapBuffers();
        
        s3eDeviceYield(0);
    }

    // Return
    return 0;
}

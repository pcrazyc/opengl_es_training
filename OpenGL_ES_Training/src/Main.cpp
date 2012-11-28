#include "s3e.h"
#include "IwGL.h"
#include "ShaderUtil.h"
#include <math.h>

const char* vertexSrc = "attribute vec4 position; uniform highp mat4 mat; varying mediump vec2 pos; void main() { gl_Position = position * mat; pos = position.xy; }";
const char* fragmentSrc = "varying mediump vec2 pos; uniform mediump float phase; void main() { gl_FragColor = vec4(1, 1, 1, 1) * sin((pos.x * pos.x + pos.y * pos.y) * 40.0 + phase); }";

const float vertices[] = {  -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f
};

//const float colors[] = { 0.0f,  1.0f,  0.0f,  1.0f,
//    0.0f,  1.0f,  0.0f,  1.0f,
//    1.0f,  0.5f,  0.0f,  1.0f,
//    1.0f,  0.5f,  0.0f,  1.0f,
//    1.0f,  0.0f,  0.0f,  1.0f,
//    1.0f,  0.0f,  0.0f,  1.0f,
//    0.0f,  0.0f,  1.0f,  1.0f,
//    1.0f,  0.0f,  1.0f,  1.0f
//};
//const float colors[] = { 1.0f,  0.0f,  0.0f,  1.0f,
//0.0f,  1.0f,  0.0f,  1.0f,
//0.0f,  0.0f,  1.0f,  1.0f,
//1.0f,  1.0f,  0.0f,  1.0f,
//0.0f,  1.0f,  1.0f,  1.0f,
//1.0f,  0.0f,  1.0f,  1.0f,
//0.5f,  0.5f,  0.0f,  1.0f,
//0.5f,  0.5f,  1.0f,  1.0f
//};
const float colors[] = { 1.0,  1.0,  0.0, 1.0,
    1.0,  0.0,  0.0,  1.0,
    0.0,  0.0,  0.0,  1.0,
    0.0,  1.0,  0.0, 1.0,  // 3
    0.0,  1.0,  1.0,  1.0, // 4
    1.0,  1.0,  1.0, 1.0,  // 5
    1.0,  0.0,  1.0, 1.0,  // 6
    0.0,  0.0,  1.0, 1.0,  // 7
};
const GLubyte Indices[] = {
    0, 4, 5, 0, 5, 1,
    1, 5, 6, 1, 6, 2,
    2, 6, 7, 2, 7, 3,
    3, 7, 4, 3, 4, 0,
    4, 7, 6, 4, 6, 5,
    3, 0, 1, 3, 1, 2
};

float m[16] = { 0.5f, 0, 0, 0,
    0, 0.5f, 0, 0,
    0, 0, 0.1f, 0,
    0, 0, 0, 1.0f
};

int main()
{
    IwGLInit();
    //GLenum shaderProgram = ShaderUtil::SharedShaderUtil()->CreateProgram(vertexSrc, fragmentSrc);
    GLenum shaderProgram = ShaderUtil::SharedShaderUtil()->CreateProgramFromFile("vertexSimple.sh", "fragmentSimple.sh");
    glUseProgram(shaderProgram);
    float offset = 0;
    GLuint _positionSlot;
    GLuint _colorSlot;
    GLuint _projectionUniform;
    GLuint _modelViewUniform;

    float step = 0;
    while(!s3eDeviceCheckQuitRequest()
        && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
        && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
        )
    {
        int w = IwGLGetInt(IW_GL_WIDTH);
        int h = IwGLGetInt(IW_GL_HEIGHT);

        glViewport(0, 0, w, h) ;
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        /*float angle = IwGLGetInt(IW_GL_ROTATE) * 3.141f / 2;
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
        offset = fmodf(offset + 0.2f, 2*3.141f);*/
        _positionSlot = glGetAttribLocation(shaderProgram, "Position");
        _colorSlot = glGetAttribLocation(shaderProgram, "SourceColor");
        _projectionUniform = glGetUniformLocation(shaderProgram, "Projection");
        _modelViewUniform = glGetUniformLocation(shaderProgram, "Modelview");

        glUniformMatrix4fv(_projectionUniform, 1, GL_FALSE, m);
        step += 0.02f;
        //step = 3.14f/8;
        /*float modelMatrix[16] = {
            cosf(step), sinf(step), 0, 0,
            -sinf(step), sinf(step), 0, 0,
            0, 0, 1.0f, 0,
            0, 0, 0, 1.0f
        };*/
        /*float modelMatrix[16] = {
            1.0f, 0, 0, 0,
            0, 1.0f, 0, 0,
            0, 0, 1.0f, 0,
            0, 0, 0, 1.0f
        };*/
        float x, y , z;
        x = 0.5f;
        y = 0.5f;
        z = 1.0f;
        float modelMatrix[16] = {
            cosf(step)+(1-cosf(step))*x*x, (1-cosf(step))*x*y-sinf(step)*z, (1-cosf(step))*x*z+sinf(step)*y, 0,
            (1-cosf(step))*x*y+sinf(step)*z, cosf(step)+(1-cosf(step))*y*y, (1-cosf(step))*y*z-sinf(step)*x, 0,
            (1-cosf(step))*x*z-sinf(step)*y, (1-cosf(step))*y*z+sinf(step)*x, cosf(step)+(1-cosf(step))*z*z, 0,
            0, 0, 0, 1.0f
        };
        glUniformMatrix4fv(_modelViewUniform, 1, GL_FALSE, modelMatrix);
        glUniform1f(glGetUniformLocation(shaderProgram, "phase"), offset);

        glEnableVertexAttribArray(_positionSlot);
        glEnableVertexAttribArray(_colorSlot);

        glVertexAttribPointer(_positionSlot, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(_colorSlot, 4, GL_FLOAT, GL_FALSE, 0, colors);
        glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, Indices);
        
        offset = fmodf(offset + 0.2f, 2*3.141f);

        IwGLSwapBuffers();

        s3eDeviceYield(0);
    }

    ShaderUtil::PurgeShaderUtil();

    return 0;
}
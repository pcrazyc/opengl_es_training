// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"
// Standard C-style entry point. This can take args if required.
int main()
{
    // Initialise the IwGx drawing module
    IwGLInit();

    // Set the background colour to (opaque) blue
    glClearColor(0, 1, 0, 1);

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

        GLfloat vVertices[] = {0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f};
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        IwGLSwapBuffers();
        s3eDeviceYield(0);
    }

    // Return
    return 0;
}

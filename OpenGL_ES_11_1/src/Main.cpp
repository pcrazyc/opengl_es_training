// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"

#include <stdlib.h>
#include <stdio.h>

// Standard C-style entry point. This can take args if required.

int main()
{
    IwGLInit();

    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);

    GLfloat color[96] = {
        1.0,  1.0,  0.0, 1.0,  // 0
        1.0,  0.0,  0.0,  1.0, // 1
        0.0,  1.0,  0.0, 1.0,  // 3
        0.0,  0.0,  0.0,  1.0, // 2

        0.0,  1.0,  0.0, 1.0,  // 3
        0.0,  1.0,  1.0,  1.0, // 4
        0.0,  0.0,  0.0, 1.0,  // 2
        0.0,  0.0,  1.0, 1.0,  // 7

        1.0,  1.0,  0.0, 1.0,  // 0
        1.0,  1.0,  1.0, 1.0,  // 5
        1.0,  0.0,  0.0, 1.0,  // 1
        1.0,  0.0,  1.0, 1.0,  // 6

        1.0,  1.0,  1.0, 1.0,  // 5
        0.0,  1.0,  1.0, 1.0,  // 4
        1.0,  0.0,  1.0, 1.0,  // 6
        0.0,  0.0,  1.0, 1.0,  // 7

        1.0,  1.0,  1.0, 1.0,  // 5
        1.0,  1.0,  0.0, 1.0,  // 0
        0.0,  1.0,  1.0, 1.0,  // 4
        0.0,  1.0,  0.0, 1.0,  // 3

        1.0,  0.0,  1.0, 1.0,  // 6
        1.0,  0.0,  0.0, 1.0,  // 1
        0.0,  0.0,  1.0, 1.0,  // 7
        0.0,  0.0,  0.0, 1.0,  // 2
    };

    GLfloat cube[72] = {

        0.5,  0.5, -0.5,   // 0
        0.5, -0.5, -0.5,   // 1
        -0.5,  0.5, -0.5,   // 3
        -0.5, -0.5, -0.5,   // 2

        -0.5,  0.5, -0.5,   // 3
        -0.5,  0.5,  0.5,   // 4
        -0.5, -0.5, -0.5,   // 2
        -0.5, -0.5,  0.5,   // 7

        0.5,  0.5, -0.5,   // 0
        0.5,  0.5,  0.5,   // 5
        0.5, -0.5, -0.5,   // 1
        0.5, -0.5,  0.5,   // 6

        0.5,  0.5,  0.5,   // 5
        -0.5,  0.5,  0.5,   // 4
        0.5, -0.5,  0.5,   // 6
        -0.5, -0.5,  0.5,   // 7

        0.5,  0.5,  0.5,   // 5
        0.5,  0.5, -0.5,   // 0
        -0.5,  0.5,  0.5,   // 4
        -0.5,  0.5, -0.5,   // 3

        0.5, -0.5,  0.5,   // 6
        0.5, -0.5, -0.5,   // 1
        -0.5, -0.5,  0.5,   // 7
        -0.5, -0.5, -0.5,   // 2
    };

    printf("Screen BPP  : %d\n", s3eSurfaceGetInt(S3E_SURFACE_PIXEL_TYPE) & S3E_SURFACE_PIXEL_SIZE_MASK);
    printf("Screen Size : %dx%d\n", w, h);
    printf("\n");
    printf( "Vendor     : %s\n", (const char*)glGetString( GL_VENDOR ) );
    printf( "Renderer   : %s\n", (const char*)glGetString( GL_RENDERER ) );
    printf( "Version    : %s\n", (const char*)glGetString( GL_VERSION ) );
    printf( "Extensions : %s\n", (const char*)glGetString( GL_EXTENSIONS ) );
    printf("\n");

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);

    glShadeModel(GL_SMOOTH);
    glRotatef(1.0, 1.0, 1.0, 1.0);
    // Loop forever, until the user or the OS performs some action to quit the app
    while(!s3eDeviceCheckQuitRequest()
          && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
          && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
          )
    {
            //To take advantage of IwGL's automatic screen rotation support, the
            //projection matrix and viewport should be set up every frame.
            int w = IwGLGetInt(IW_GL_WIDTH);
            int h = IwGLGetInt(IW_GL_HEIGHT);
            glViewport( 0, 0, w, h );
            glMatrixMode( GL_PROJECTION );
            glLoadIdentity( );

            glOrthof( -2.0, 2.0, -2.0, 2.0, -20.0, 20.0 );

            /* Do our drawing, too. */
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4, GL_FLOAT, 0, color);
            glVertexPointer(3, GL_FLOAT, 0, cube);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            glMatrixMode(GL_MODELVIEW);
            glRotatef(1.0, 1.0, 1.0, 1.0);

            // Call IwGL swap instead of egl directly
            IwGLSwapBuffers();
        
        s3eDeviceYield(0);
    }

    // Return
    return 0;
}

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
    const float colors[] = { 1.0,  1.0,  0.0, 1.0,
        1.0,  0.0,  0.0,  1.0,
        0.0,  0.0,  0.0,  1.0,
        0.0,  1.0,  0.0, 1.0,
        0.0,  1.0,  1.0,  1.0,
        1.0,  1.0,  1.0, 1.0,
        1.0,  0.0,  1.0, 1.0,
        0.0,  0.0,  1.0, 1.0,
    };

    const GLubyte Indices[] = {
        0, 4, 5, 0, 5, 1,
        1, 5, 6, 1, 6, 2,
        2, 6, 7, 2, 7, 3,
        3, 7, 4, 3, 4, 0,
        4, 7, 6, 4, 6, 5,
        3, 0, 1, 3, 1, 2
    };
    printf("Screen BPP  : %d\n", s3eSurfaceGetInt(S3E_SURFACE_PIXEL_TYPE) & S3E_SURFACE_PIXEL_SIZE_MASK);
    printf("Screen Size : %dx%d\n", w, h);
    printf("\n");
    printf( "Vendor     : %s\n", (const char*)glGetString( GL_VENDOR ) );
    printf( "Renderer   : %s\n", (const char*)glGetString( GL_RENDERER ) );
    printf( "Version    : %s\n", (const char*)glGetString( GL_VERSION ) );
    printf( "Extensions : %s\n", (const char*)glGetString( GL_EXTENSIONS ) );
    printf("\n");

    

    //glDepthFunc(GL_LESS);

    //glShadeModel(GL_SMOOTH);
    //glRotatef(1.0, 1.0, 1.0, 1.0);

    glViewport( 0, 0, w, h );
    //glFrustumf(-3, 3, -2.0, 2.0, 0.1f, 20.0f);
    
    
    //glMatrixMode(GL_MODELVIEW);
    //glTranslatef(0.0f, 0.0f, 5.0f);
    //glRotatef(90.0f, 0.0, 1.0, 0.0);
        // Call IwGL swap instead of egl directly
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    //glOrthof( -3, 3, -2.0, 2.0, 1.0f, 4.0f );
    glFrustumf( -3, 3, -2.0, 2.0, 1.0f, 4.0f );
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
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
        

        /* Do our drawing, too. */
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, colors);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, Indices);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        IwGLSwapBuffers();

        s3eDeviceYield(0);
    }

    // Return
    return 0;
}
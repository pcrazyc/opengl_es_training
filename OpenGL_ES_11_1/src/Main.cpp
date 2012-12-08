// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"

#include <stdlib.h>
#include <stdio.h>

#include "Cylinder.h"

extern Vertex3D cylinderCenter;
extern float cylinderRadius;
extern float cylinderHeight;

// Standard C-style entry point. This can take args if required.

int main()
{
    IwGLInit();

    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);

    glViewport( 0, 0, w, h );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    //glOrthof( -3, 3, -2.0, 2.0, 1.0f, 4.0f );
    
    glFrustumf( -3, 3, -2.0, 2.0, 0.1f, 3.0f );
    glTranslatef(0.0f, 0.0f, -2.0f);
    //glRotatef(45.0f, 0.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    Cylinder *aCylinder = new Cylinder(cylinderCenter, cylinderRadius, cylinderHeight);
    while(!s3eDeviceCheckQuitRequest()
        && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
        && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
        )
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        aCylinder->draw();

        /*glMatrixMode(GL_MODELVIEW);
        glTranslatef(0.0f, 0.0f, 5.0f);
        glRotatef(1.0f, 1.0, 1.0, 1.0);*/

        IwGLSwapBuffers();

        s3eDeviceYield(0);
    }

    // Return
    return 0;
}
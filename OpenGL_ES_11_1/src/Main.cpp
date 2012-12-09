// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"

#include <stdlib.h>
#include <stdio.h>

#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "Cuboid.h"

extern Vertex3D cylinderCenter;
extern float cylinderRadius;
extern float cylinderHeight;

extern Vertex3D coneCenter;
extern float coneRadius;
extern float coneHeight;

extern Vertex3D sphereCenter;
extern float sphereRadius;

extern Vertex3D cubeOrigin;
extern Vertex3D cubeRight;
extern Vertex3D cubeTop;
extern Vertex3D cubeFront;

extern Vertex3D cuboidOrigin;
extern Vertex3D cuboidRight;
extern Vertex3D cuboidTop;
extern Vertex3D cuboidFront;

// Standard C-style entry point. This can take args if required.

int main()
{
    IwGLInit();

    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);

    glViewport( 0, 0, w, h );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    //glFrustumf( -3, 3, -2.0, 2.0, 0.1f, 10.0f );
    
    glOrthof( -3.0f, 3.0f, -2.0f, 2.0f, -10.0f, 10.0f );
    glTranslatef(0.0f, 0.0f, -2.0f);
    //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    //Shape *aShape = new Cylinder(cylinderCenter, cylinderRadius, cylinderHeight);
    //Shape *aShape = new Cone(coneCenter, coneRadius, coneHeight);
    Shape *aShape = new Sphere(sphereCenter, sphereRadius);
    //Shape *aShape = new Cuboid(cubeOrigin, cubeRight, cubeTop, cubeFront);
    //Shape *aShape = new Cuboid(cuboidOrigin, cuboidRight, cuboidTop, cuboidFront);
    while(!s3eDeviceCheckQuitRequest()
        && !(s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
        && !(s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)
        )
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        aShape->draw();

        glMatrixMode(GL_MODELVIEW);
        glRotatef(1.0f, 1.0, 1.0, 1.0);

        IwGLSwapBuffers();

        s3eDeviceYield(0);
    }

    // Return
    return 0;
}
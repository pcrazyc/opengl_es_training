// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"

#include <stdlib.h>
#include <stdio.h>
#include "Input.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "Cuboid.h"

// Attempt to lock to 25 frames per second
#define MS_PER_FRAME (1000 / 25)

extern Vertex3D cylinderCenter;
extern float cylinderRadius;
extern float cylinderHeight;

extern Vertex3D coneCenter;
extern float coneRadius;
extern float coneHeight;

extern Vertex3D sphereCenter;
extern float sphereRadius;

extern float cubeX;
extern float cubeY;
extern float cubeZ;

extern float cuboidX;
extern float cuboidY;
extern float cuboidZ;



void SetModel()
{
	//Shape *aShape = new Cylinder(cylinderCenter, cylinderRadius, cylinderHeight);
	//Shape *aShape = new Cone(coneCenter, coneRadius, coneHeight);
	//Shape *aShape = new Sphere(sphereCenter, sphereRadius);
	//Shape *aShape = new Cuboid(cubeOrigin, cubeRight, cubeTop, cubeFront);
	//Shape *aShape = new Cuboid(cuboidOrigin, cuboidRight, cuboidTop, cuboidFront);

}


void SetLight()
{
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    const GLfloat light0Ambient[] = {0.05, 0.05, 0.05, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

    const GLfloat light0Diffuse[] = {1, 1, 1, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    const GLfloat light0Position[] = {10.0, 10.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

    GLfloat ambientAndDiffuse[] = {0.0, 0.1, 0.9, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);
    GLfloat specular[] = {0.3, 0.3, 0.3, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);

}

bool Update()
{
	if (g_CameraOpe  & CAMERA_LEFT)
	{
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0.1, 0 ,0);
	}
	if (g_CameraOpe  & CAMERA_RIGHT)
	{
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(-0.1, 0 ,0);
	}
	if (g_CameraOpe  & CAMERA_UP)
	{
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0, 0.1 ,0);

	}
	if (g_CameraOpe  & CAMERA_DOWN)
	{
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0, -0.1 ,0);
	
	}
	if (g_CameraOpe  & CAMERA_NEAR)
	{
		
	}
	if (g_CameraOpe  & CAMERA_FAR)
	{
		
	}
	return true;

}

void Draw()
{
	//int w = IwGLGetInt(IW_GL_WIDTH);
	//int h = IwGLGetInt(IW_GL_HEIGHT);

	///* Do our drawing, too. */
	//glClearColor(0.1, 0.1, 0.1, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	//glColorPointer(4, GL_FLOAT, 0, colors);
	//glVertexPointer(3, GL_FLOAT, 0, vertices);
	//glDrawElements(GL_TRIANGLES, sizeof(Indices)/sizeof(Indices[0]), GL_UNSIGNED_BYTE, Indices);
	////glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	//glMatrixMode(GL_MODELVIEW);
	////glTranslatef(0.0f, 0.0f, 5.0f);
	//glRotatef(1.0f, 1.0, 1.0, 1.0);

	//IwGLSwapBuffers();

	//s3eDeviceYield(0);

}

int main()
{
    IwGLInit();
	InputInit();


    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);
    glShadeModel(GL_SMOOTH);
    //glRotatef(1.0, 1.0, 1.0, 1.0);
    glViewport( 0, 0, w, h );

	Shape *aCube = new Cuboid( cubeX, cubeY, cubeZ );
	Shape *aCuboid = new Cuboid( cuboidX, cuboidY, cuboidZ );
	Shape *aCylinder = new Cylinder( cylinderRadius, cylinderHeight );
	Shape *aCone = new Cone( coneRadius, coneHeight );
	Shape *aSphere = new Sphere( sphereRadius );

	aCube->SetPos(-3.0f, -0.5f);
	aCuboid->SetPos(-0.5f, -4.0f);
	aSphere->SetPos(0.0f);
	aCone->SetPos(3.0f);
	aCylinder->SetPos(0.0f, 3.0f);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    glFrustumf( -4.0f, 4.0f, -4.0, 4.0, 2.0f, 5.0f );
	//glOrthof(-15.0f, 15.0f, -5.0, 5.0, 1.0f, 10.0f);
    glTranslatef(0.0f, 0.0f, -3.5f);
    //glRotatef(10.0f, 0.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	SetLight();

	
	


	while(1)
	{
		int64 start = s3eTimerGetMs();

		bool aResult = Update();
		if (aResult== false || s3eDeviceCheckQuitRequest()
			|| (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
			|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN))
		{
			break;
		}
		aCube->Update();
		aCuboid->Update();
		aCylinder->Update();
		aCone->Update();
		aSphere->Update();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		aCube->Draw();
		aCuboid->Draw();
		aCylinder->Draw();
		aCone->Draw();
		aSphere->Draw();


		IwGLSwapBuffers();
		
		//// Attempt frame rate
		while ((s3eTimerGetMs() - start) < MS_PER_FRAME)
		{
			int32 yield = (int32) (MS_PER_FRAME - (s3eTimerGetMs() - start));
			if (yield<0)
				break;
			s3eDeviceYield(yield);
		}		
		
	}

    // Return
    return 0;
}
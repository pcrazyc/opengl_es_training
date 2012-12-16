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
#include <list>
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


Vertex3D gCameraVec;

FVector3 pos(0.0f, 0.f, -14.0f);
FVector3 target(0.0f, 0.0f, 0.0f);
FVector3 up(0.0f, 1.0f, 0.0f);
float zNear = 1.0f;
float zFar = 1000.0f;

std::list<Shape *> shapeList;

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
    const GLfloat light0Ambient[] = {1.0f, 0.05f, 0.05f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

    const GLfloat light0Diffuse[] = {1, 1, 1, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    const GLfloat light0Position[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

    /*GLfloat ambientAndDiffuse[] = {0.0f, 0.1f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);
    GLfloat specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);*/
    
    
    //// Enable lighting
    //glEnable(GL_LIGHTING);

    //// Turn the first light on
    //glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);

    //// Define the ambient component of the first light
    //const GLfloat light0Ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    //glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

    //// Define the diffuse component of the first light
    //const GLfloat light0Diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    //// Define the specular component and shininess of the first light
    //const GLfloat light0Specular[] = {0.7f, 0.7f, 0.7f, 1.0f};
    //const GLfloat light0Shininess = 0.4f;
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);


    //// Define the position of the first light
    //const GLfloat light0Position[] = {0.0f, 10.0f, 10.0f, 0.0f};
    //glLightfv(GL_LIGHT0, GL_POSITION, light0Position); 

    //// Define a direction vector for the light, this one points right down the Z axis
    //const GLfloat light0Direction[] = {0.0f, 0.0f, -1.0f};
    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0Direction);

    //// Define a cutoff angle. This defines a 90бу field of vision, since the cutoff
    //// is number of degrees to each side of an imaginary line drawn from the light's
    //// position along the vector supplied in GL_SPOT_DIRECTION above
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);

}

void UpdateCamera()
{
	if (g_CameraOpe  & CAMERA_LEFT)
	{
		target.x += 0.1f;
	}
	if (g_CameraOpe  & CAMERA_RIGHT)
	{
		target.x -= 0.1f;
	}
	if (g_CameraOpe  & CAMERA_UP)
	{
		target.y += 0.2f;
	}
	if (g_CameraOpe  & CAMERA_DOWN)
	{
		target.y -= 0.2f;
	}
	if (g_CameraOpe  & CAMERA_NEAR)
	{
		pos.z += 0.1f;
	}
	if (g_CameraOpe  & CAMERA_FAR)
	{
		pos.z -= 0.1f;
	}
	if (g_CameraOpe  & CAMERA_ZOOM_IN)
	{
		//zNear += 0.1f;
		//target.z += 0.1f;
	}
	if (g_CameraOpe  & CAMERA_ZOOM_OUT)
	{
		//target.z -= 0.1f;
		/*zNear -= 0.1f;
		if (zNear < 0.1f)
		{
			zNear = 0.1f;
		}*/
	}
	//printf("%f\n", zNear);

}

void Draw()
{

}

void SetCliping(float zNear, float zFar, float angle)
{
	float aspectRatio;
	int w = IwGLGetInt(IW_GL_WIDTH);
	int h = IwGLGetInt(IW_GL_HEIGHT);
	GLfloat size;
	aspectRatio= (float)w / (float)h; //5

	////Set the OpenGL projection matrix.
	glMatrixMode(GL_PROJECTION); //6
	glLoadIdentity();
	size = zNear * tanf( (angle) / 2.0f); //7
	glFrustumf(-size, size, -size /aspectRatio, size /aspectRatio, zNear, zFar); //8

	glViewport( 0, 0, w, h );

}

int main()
{
    IwGLInit();
	InputInit();

    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);
    glShadeModel(GL_SMOOTH);

	//SetCliping(1.0f, 1000.0f, PI / 3.0f);
	SetCliping(zNear, zFar,  PI / 3.0f);
	
	glMatrixMode( GL_MODELVIEW );
	suLookAt(pos.x, pos.y, pos.z, target.x, target.y, target.z, up.x, up.y, up.z);
   
	glEnable(GL_DEPTH_TEST);
	SetLight();

    Shape *pCube = new Cuboid( cubeX, cubeY, cubeZ );
    pCube->SetPos(0, -8, 0);
    shapeList.push_back(pCube);

    Shape *pCuboid = new Cuboid( cuboidX, cuboidY, cuboidZ );
    pCuboid->SetPos(-4, 0, 0);
    shapeList.push_back(pCuboid);

    Shape *pCylinder = new Cylinder( cylinderRadius, cylinderHeight );
    pCylinder->SetPos(-2.0f, 0, 0);
    shapeList.push_back(pCylinder);

    Shape *pCone = new Cone( coneRadius, coneHeight );
    pCone->SetPos(4, 0, 0);
    shapeList.push_back(pCone);

    Shape *pSphere = new Sphere( sphereRadius );
	pSphere->SetPos(0, 4, 0);
    shapeList.push_back(pSphere);

	while(1)
	{
		int64 start = s3eTimerGetMs();

		if (s3eDeviceCheckQuitRequest()
			|| (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
			|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN))
		{
			break;
		}

		UpdateCamera();
		SetCliping(zNear, zFar,  PI / 3.0f);

		for (std::list<Shape *>::iterator it=shapeList.begin(); it!=shapeList.end(); it++) {
            (*it)->Update();
        }

		//Draw();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//glTranslatef(gCameraVec.x, gCameraVec.y ,gCameraVec.z);
		suLookAt(pos.x, pos.y, pos.z, target.x, target.y, target.z, up.x, up.y, up.z);

        for (std::list<Shape *>::iterator it=shapeList.begin(); it!=shapeList.end(); it++) {
            (*it)->Draw();
        }

		//TouchRender();
		//s3eSurfaceShow();
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
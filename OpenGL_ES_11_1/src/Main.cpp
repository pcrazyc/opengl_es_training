// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"
#include "ConfigManager.h"
#include <stdlib.h>
#include <stdio.h>
#include "Input.h"
#include "ShapeManager.h"
#include "MathUtil.h"

// Attempt to lock to 25 frames per second
#define MS_PER_FRAME (1000 / 25)


FVector3 pos(0.0f, 0.f, -10.0f);
FVector3 target(0.0f, 0.0f, 0.0f);
FVector3 up(0.0f, 1.0f, 0.0f);
float zNear = 1.0f;
float zFar = 1000.0f;
float angle = PI / 3.0f;

#define LOAD_FILE_FRAME 200
#define FRAME_MAX 1000000

int indexFrame;

void SetModel()
{
	ShapeManager& theShapeManager = ShapeManager::GetInstance();
	Shape *aCylinder = theShapeManager.CreatShape(E_CYLINDER);
	aCylinder->SetPos(-3.0f, 0, 0);

	Shape *aCone = theShapeManager.CreatShape(E_CONE);
	aCone->SetPos(3.0f, 0, 0);

	Shape *aSphere = theShapeManager.CreatShape(E_SPHERE);
	aSphere->SetPos(0, 0, 0);

	Shape *aCube = theShapeManager.CreatShape(E_CUBE);
	aCube->SetPos(0, -2.0f, 0);

	Shape *aCuboid = theShapeManager.CreatShape(E_CUBOID);
	aCuboid->SetPos(0, 2.5f, 0);

}


void SetLight()
{
	/*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    const GLfloat light0Ambient[] = {1.0f, 0.05f, 0.05f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

    const GLfloat light0Diffuse[] = {1, 1, 1, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    const GLfloat light0Position[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);*/

    /*GLfloat ambientAndDiffuse[] = {0.0f, 0.1f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);
    GLfloat specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 25.0);*/
    
    
    // Enable lighting
    glEnable(GL_LIGHTING);

    // Turn the first light on
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Define the ambient component of the first light
    const GLfloat light0Ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);

    // Define the diffuse component of the first light
    const GLfloat light0Diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);

    const GLfloat light0Specular[] = {0.7f, 0.7f, 0.7f, 1.0f};
    const GLfloat light0Shininess = 0.4f;
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);


    // Define the position of the first light
    const GLfloat light0Position[] = {2.0f, 2.0f, -1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position); 
    const GLfloat light0Direction[] = {-2.0f, -2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0Direction);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);

	/*GLfloat ambientAndDiffuse[] = {0.0, 0.1, 0.9, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);*/
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
		target.y += 0.1f;
	}
	if (g_CameraOpe  & CAMERA_DOWN)
	{
		target.y -= 0.1f;
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
		printf("test zoom in\n");
		if (angle < PI / 2.0f )
		{
			angle += 0.03f;
		}
	}
	if (g_CameraOpe  & CAMERA_ZOOM_OUT)
	{
		printf("test zoom out\n");
		if (angle > PI / 4.0f)
		{
			angle -= 0.03f;
		}
	}

}

void SetCliping(float zNear, float zFar, float angle)
{
	float aspectRatio;
	int w = IwGLGetInt(IW_GL_WIDTH);
	int h = IwGLGetInt(IW_GL_HEIGHT);
	GLfloat size;
	aspectRatio= (float)w / (float)h;  

	////Set the OpenGL projection matrix.
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	size = zNear * tanf( (angle) / 2.0f);
	glFrustumf(-size, size, -size /aspectRatio, size /aspectRatio, zNear, zFar); //8

	glViewport( 0, 0, w, h );

}

void Update() {
	indexFrame++;

	indexFrame = indexFrame%FRAME_MAX;

	if (indexFrame%LOAD_FILE_FRAME == 0) {
		//TODO detect file
		ShapeManager::GetInstance().Reset();
	}
}

int main()
{
    IwGLInit();
	InputInit();

    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);
    glShadeModel(GL_SMOOTH);

	//SetCliping(zNear, zFar,  PI / 3.0f);
	SetCliping(zNear, zFar, angle);
	
	glMatrixMode( GL_MODELVIEW );
	suLookAt(pos.x, pos.y, pos.z, target.x, target.y, target.z, up.x, up.y, up.z);
   
	glEnable(GL_DEPTH_TEST);
	SetLight();

	SetModel();
	indexFrame = 0;
	while(1)
	{
		int64 start = s3eTimerGetMs();

		if (s3eDeviceCheckQuitRequest()
			|| (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
			|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN))
		{
			ShapeManager& theShapeManager = ShapeManager::GetInstance();
			theShapeManager.ClearAll();
			break;
		}

		Update();

		UpdateCamera();
		//SetCliping(zNear, zFar,  PI / 3.0f);
		SetCliping(zNear, zFar, angle);

		ShapeManager& theShapeManager = ShapeManager::GetInstance();
		theShapeManager.Update(0);

		//Draw();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		
		//glTranslatef(gCameraVec.x, gCameraVec.y ,gCameraVec.z);
		suLookAt(pos.x, pos.y, pos.z, target.x, target.y, target.z, up.x, up.y, up.z);

		theShapeManager.Draw();

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
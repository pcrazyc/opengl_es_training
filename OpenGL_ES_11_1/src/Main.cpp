// Include header files for S3E (core system) and IwGx (rendering) modules
#include "s3e.h"
#include "IwGL.h"
#include "ConfigManager.h"
#include <stdlib.h>
#include <stdio.h>
#include "Input.h"
#include "ShapeManager.h"
#include "MathUtil.h"
#include "UILayer.h"


FVector3 g_pos(0.0f, 0.f, -8.0f);
FVector3 g_target(0.0f, 0.0f, 0.0f);
FVector3 g_up(0.0f, 1.0f, 0.0f);
float g_zNear = 1.0f;
float g_zFar = 1000.0f;
float g_angle = PI / 3.0f;

double g_fps = 0.0f;

// Attempt to lock to 25 frames per second
//#define MS_PER_FRAME (1000 / 25)
#define INDEX_FRAME_MAX 1000000
#define INDEX_FRAME_LOAD_CONFIG 200

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

void SetUI(int theWidth, int theHeight)
{
	UILayer& theUILayer = UILayer::GetInstance();
	theUILayer.Init(theWidth, theHeight);
}

void UpdateUIText()
{
	UILayer& theUILayer = UILayer::GetInstance();
	//theUILayer.Init(theWidth, theHeight);


	static char aBuffer[512];
	snprintf(aBuffer,512, "camera:\n pos (%5.2f,%5.2f,%5.2f) \n target (%5.2f, %5.2f, %5.2f)\n up (%5.2f, %5.2f, %5.2f) \n fps: %4.3f", 
		g_pos.x, g_pos.y, g_pos.z, g_target.x, g_target.y, g_target.z, g_up.x, g_up.y, g_up.z, g_fps);

	theUILayer.SetPrintText(aBuffer);
};

void SetLight()
{    
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
    const GLfloat light0Position[] = {2.0f, 2.0f, -3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position); 
    const GLfloat light0Direction[] = {-2.0f, -2.0f, 3.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0Direction);

    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);

	/*GLfloat ambientAndDiffuse[] = {0.0, 0.1, 0.9, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambientAndDiffuse);*/

}

void UpdateCamera()
{
	if (g_CameraOpe  & CAMERA_LEFT)
	{
		g_target.x += 0.2f;
	}
	if (g_CameraOpe  & CAMERA_RIGHT)
	{
		g_target.x -= 0.2f; 
	}
	if (g_CameraOpe  & CAMERA_UP)
	{
		g_target.y += 0.2f;
	}
	if (g_CameraOpe  & CAMERA_DOWN)
	{
		g_target.y -= 0.2f;
	}
	if (g_CameraOpe  & CAMERA_NEAR)
	{
		g_pos.z += 0.1f;
	}
	if (g_CameraOpe  & CAMERA_FAR)
	{
		g_pos.z -= 0.1f;
	}
	if (g_CameraOpe  & CAMERA_ZOOM_IN)
	{
		printf("test zoom in\n");
		if (g_angle < PI / 2.0f )
		{
			g_angle += 0.02f;
		}
	}
	if (g_CameraOpe  & CAMERA_ZOOM_OUT)
	{
		printf("test zoom out\n");
		if (g_angle > PI / 4.0f)
		{
			g_angle -= 0.02f;
		}
	}

}

void SetCliping(float g_zNear, float g_zFar, float g_angle)
{
	float aspectRatio;
	int w = IwGLGetInt(IW_GL_WIDTH);
	int h = IwGLGetInt(IW_GL_HEIGHT);
	GLfloat size;
	aspectRatio= (float)w / (float)h;  

	////Set the OpenGL projection matrix.
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	size = g_zNear * tanf( (g_angle) / 2.0f);  
	glFrustumf(-size, size, -size /aspectRatio, size /aspectRatio, g_zNear, g_zFar);  

	glViewport( 0, 0, w, h );

}

void Update() {
	indexFrame++;

	indexFrame = indexFrame % INDEX_FRAME_MAX;

	if (indexFrame % INDEX_FRAME_LOAD_CONFIG == 0) {
		ConfigManager::PurgeConfigManager();
		ShapeManager::GetInstance().Reset();
	}
}

int main()
{
	int frames;
	uint64 start_time, this_time;

    IwGLInit();
	InputInit();

    int w = IwGLGetInt(IW_GL_WIDTH);
    int h = IwGLGetInt(IW_GL_HEIGHT);
    glShadeModel(GL_SMOOTH);

	//SetCliping(g_zNear, g_zFar,  PI / 3.0f);
	SetCliping(g_zNear, g_zFar, g_angle);
	
	glMatrixMode( GL_MODELVIEW );
	suLookAt(g_pos.x, g_pos.y, g_pos.z, g_target.x, g_target.y, g_target.z, g_up.x, g_up.y, g_up.z);
   
	glEnable(GL_DEPTH_TEST);
	SetLight();

	SetModel();
	SetUI(IwGLGetInt(IW_GL_WIDTH), IwGLGetInt(IW_GL_HEIGHT));

	start_time = (int)s3eTimerGetMs();
	frames = 0;
	while(1)
	{
		if (s3eDeviceCheckQuitRequest()
			|| (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN)
			|| (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN))
		{
			ShapeManager& theShapeManager = ShapeManager::GetInstance();
			theShapeManager.ClearAll();
			break;
		}

		//Update();
		UpdateCamera();
		//SetCliping(g_zNear, g_zFar,  PI / 3.0f);
		SetCliping(g_zNear, g_zFar, g_angle);

		ShapeManager& theShapeManager = ShapeManager::GetInstance();
		theShapeManager.Update(0);

		UpdateUIText();
		UILayer& theUILayer = UILayer::GetInstance();
		theUILayer.Update(0);

		//Draw();
		glClearColor(0.2f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		
		//glTranslatef(gCameraVec.x, gCameraVec.y ,gCameraVec.z);
		suLookAt(g_pos.x, g_pos.y, g_pos.z, g_target.x, g_target.y, g_target.z, g_up.x, g_up.y, g_up.z);

		theShapeManager.Draw();
		theUILayer.Draw();

		IwGLSwapBuffers();
		s3eDeviceYield(0);
		
		//cal fps
		++frames;
		{
			this_time = s3eTimerGetMs();
			if (frames > 10)
			{
				g_fps = (double)frames/(this_time-start_time)*1000.0;
				start_time = this_time;
				frames = 0;
			}
		}
	}

    // Return
    return 0;
}
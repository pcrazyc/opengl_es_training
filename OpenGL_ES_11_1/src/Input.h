#ifndef INPUT_H
#define INPUT_H

#include "s3eKeyboard.h"
#include "ShapeManager.h"

#define CAMERA_NULL			0x0000
#define	CAMERA_LEFT			0x0001 
#define	CAMERA_RIGHT		0x0002 
#define	CAMERA_UP			0x0004 
#define	CAMERA_DOWN			0x0008 
#define	CAMERA_NEAR			0x0010 
#define	CAMERA_FAR			0x0020  
#define	CAMERA_ZOOM_IN		0x0040 
#define	CAMERA_ZOOM_OUT		0x0080 

int32 g_CameraOpe = CAMERA_NULL;
char g_TouchEventMsg[128] = {0};

enum TOUCH_MOVE_DIRECTION
{
	TOUCH_MOVE_NULL,
	TOUCH_MOVE_LEFT,
	TOUCH_MOVE_RIGHT,
	TOUCH_MOVE_UP,
	TOUCH_MOVE_DOWN,
};


//Simple structure to track touches
struct CTouch
{
	int32 x; // position x
	int32 y; // position y
	bool active; // is touch active (currently down)
	int32 id; // touch's unique identifier
	TOUCH_MOVE_DIRECTION direction; //add by raoyj
};
bool g_UseMultiTouch = true;

#define MAX_TOUCHES 2
CTouch g_Touches[MAX_TOUCHES];

//Find an active touch with the specified id, or allocate a free one from the list
CTouch* GetTouch(int32 id)
{
	CTouch* pInActive = NULL;

	for (uint32 i = 0; i < MAX_TOUCHES; i++)
	{
		if (id == g_Touches[i].id)
			return &g_Touches[i];
		if (!g_Touches[i].active)
			pInActive = &g_Touches[i];
			//break;					
	}

	//Return first inactive touch
	if (pInActive)
	{
		pInActive->id = id;
		return pInActive;
	}

	//No more touches, give up.
	return NULL;
}

void MultiTouchButtonCB(s3ePointerTouchEvent* event)
{
	printf("x: %d, y: %d\n", event->m_x, event->m_y);
	if (!event->m_Pressed && event->m_x>460 && event->m_y>300) {
		ConfigManager::PurgeConfigManager();
		ShapeManager::GetInstance().Reset();
	}
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch)
	{
		touch->active = event->m_Pressed != 0;
		touch->direction = TOUCH_MOVE_NULL;
		touch->x = event->m_x;
		touch->y = event->m_y;
	}
	g_CameraOpe = CAMERA_NULL;
	sprintf(g_TouchEventMsg, "`x666666Touch %u %s ",event->m_TouchID, event->m_Pressed ? "PRESSED" : "RELEASED");
	//printf("x666666Touch %u %s\n",event->m_TouchID, event->m_Pressed ? "PRESSED" : "RELEASED");
}

void PrintfTest()
{
	for (uint32 i = 0; i < MAX_TOUCHES; i++)
	{
		if (g_Touches[i].active)
		{
			printf("active index = %d, id =%d \n",i, g_Touches[i].id);
		}
	}

}

void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
	CTouch* touch = GetTouch(event->m_TouchID);

	int oldX = touch->x;
	int oldY = touch->y;
	touch->x = event->m_x;
	touch->y = event->m_y;

	int disX = touch->x - oldX;
	int disY = touch->y - oldY;
	if (abs(disX) > abs(disY))
	{
		touch->direction = disX < 0 ? TOUCH_MOVE_LEFT : disX > 0 ? TOUCH_MOVE_RIGHT : TOUCH_MOVE_NULL;
	}
	else
	{
		touch->direction = disY < 0 ? TOUCH_MOVE_UP : disX > 0 ? TOUCH_MOVE_DOWN : TOUCH_MOVE_NULL;
	}

	//PrintfTest();
	if (g_Touches[0].active == true && g_Touches[1].active == true)
	{
		 if (g_Touches[0].direction == TOUCH_MOVE_LEFT && g_Touches[1].direction == TOUCH_MOVE_LEFT)
		 {
			g_CameraOpe |= CAMERA_NEAR;
			printf("****CAMERA_NEAR\n");
		 }
		 if (g_Touches[0].direction == TOUCH_MOVE_RIGHT && g_Touches[1].direction == TOUCH_MOVE_RIGHT)
		 {
			 g_CameraOpe |= CAMERA_FAR;
			 printf("****CAMERA_FAR\n");
		 }
		 if (g_Touches[0].direction == TOUCH_MOVE_UP && g_Touches[1].direction == TOUCH_MOVE_UP)
		 {
			 g_CameraOpe |= CAMERA_ZOOM_IN;
			 printf("****CAMERA_ZOOM_IN\n");
		 }
		 if (g_Touches[0].direction == TOUCH_MOVE_DOWN && g_Touches[1].direction == TOUCH_MOVE_DOWN)
		 {
			 g_CameraOpe |= CAMERA_ZOOM_OUT;
			 printf("****CAMERA_ZOOM_OUT\n");
		 }
	}
	else if (g_Touches[0].active == true)
	{
		if (g_Touches[0].direction == TOUCH_MOVE_LEFT)
		{
			g_CameraOpe |= CAMERA_LEFT;
		}
		else if (g_Touches[0].direction == TOUCH_MOVE_RIGHT)
		{
			g_CameraOpe |= CAMERA_RIGHT;
		}
		else if (g_Touches[0].direction == TOUCH_MOVE_UP)
		{
			g_CameraOpe |= CAMERA_UP;
		}
		else if (g_Touches[0].direction == TOUCH_MOVE_DOWN)
		{
			g_CameraOpe |= CAMERA_DOWN;
		}

	}

}

void SingleTouchButtonCB(s3ePointerEvent* event)
{
	g_Touches[0].active = event->m_Pressed != 0;
	g_Touches[0].x = event->m_x;
	g_Touches[0].y = event->m_y;

	g_CameraOpe = CAMERA_NULL;
	sprintf(g_TouchEventMsg, "`x666666Touch %s", event->m_Pressed ? "PRESSED" : "RELEASED");
}

void SingleTouchMotionCB(s3ePointerMotionEvent* event)
{
	if (event->m_x < g_Touches[0].x)
	{
		g_CameraOpe |= CAMERA_LEFT;
	}
	if (event->m_x > g_Touches[0].x)
	{
		g_CameraOpe |= CAMERA_RIGHT;
	}
	if (event->m_y < g_Touches[0].y)
	{
		g_CameraOpe |= CAMERA_UP;
	}
	if (event->m_y > g_Touches[0].y)
	{
		g_CameraOpe |= CAMERA_DOWN;
	}
	g_Touches[0].x = event->m_x;
	g_Touches[0].y = event->m_y;

}

void InputInit()
{
	//g_UseMultiTouch = false;
	g_UseMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
	if (g_UseMultiTouch)
	{
		//Register for multi touch events on platforms where the functionality is available.
		s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
		s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
	}
	else
	{
		//Register for standard pointer events
		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
		s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
	}
}

void TouchRender()
{
	 s3eDebugPrint(20, 50, g_TouchEventMsg, 1);
}
#endif
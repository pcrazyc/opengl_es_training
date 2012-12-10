#ifndef INPUT_H
#define INPUT_H

#include "s3eKeyboard.h"

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

//Simple structure to track touches
struct CTouch
{
	int32 x; // position x
	int32 y; // position y
	bool active; // is touch active (currently down)
	int32 id; // touch's unique identifier
};
bool g_UseMultiTouch = false;

#define MAX_TOUCHES 10
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
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch)
	{
		touch->active = event->m_Pressed != 0;
		touch->x = event->m_x;
		touch->y = event->m_y;
	}
	g_CameraOpe = CAMERA_NULL;
	//sprintf(g_TouchEventMsg, "`x666666Touch %u %s",event->m_TouchID, event->m_Pressed ? "PRESSED" : "RELEASED");
}

void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
	CTouch* touch = GetTouch(event->m_TouchID);
	if (touch)
	{
		if (event->m_x < touch->x)
		{
			g_CameraOpe |= CAMERA_NEAR;
		}
		else if (event->m_x > touch->x)
		{
			g_CameraOpe |= CAMERA_FAR;
		}
		else if (event->m_y < touch->y)
		{
			g_CameraOpe |= CAMERA_ZOOM_IN;
		}
		else if (event->m_y < touch->y)
		{
			g_CameraOpe |= CAMERA_ZOOM_OUT;
		}

		touch->x = event->m_x;
		touch->y = event->m_y;
	}

}

void SingleTouchButtonCB(s3ePointerEvent* event)
{
	g_Touches[0].active = event->m_Pressed != 0;
	g_Touches[0].x = event->m_x;
	g_Touches[0].y = event->m_y;

	g_CameraOpe = CAMERA_NULL;
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
	if (event->m_y < g_Touches[0].y)
	{
		g_CameraOpe |= CAMERA_DOWN;
	}
	g_Touches[0].x = event->m_x;
	g_Touches[0].y = event->m_y;
}

void InputInit()
{
	g_UseMultiTouch = false;
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

#endif
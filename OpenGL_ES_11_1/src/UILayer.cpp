#include "UILayer.h"
#include "Font.h"



UILayer::UILayer()
{
	mFont = NULL;
	mWidth = 0;
	mHeight = 0;
}

UILayer::~UILayer()
{
	Destory();
}

void UILayer::Init(int theWidth, int theHeight)
{
	mWidth = theWidth;
	mHeight = theHeight;
	mFont = new Font();
	mFont->Init("font.raw");
	mFont->SetScale(0.3f);
}

void UILayer::Destory()
{
	if (mFont)
	{
		delete mFont;
		mFont = NULL;
	}
}

void UILayer::Update(float delta)
{


}

void UILayer::SetPrintText(char* theTxt)
{
	mPrintText = theTxt;
}

void UILayer::Draw()
{
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrthof(0,mWidth,0,mHeight,-1.0f,1.0f);					// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslatef(0,0,-1);								// Position The Text (0,0 - Bottom Left)

	//mFont->DrawText("-595.6", 50, 20);
	mFont->DrawText(mPrintText,0, 280);

	//glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

}
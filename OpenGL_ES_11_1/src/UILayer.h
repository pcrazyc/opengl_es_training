#pragma once
#include <string>
#include "IwGL.h"
 
class Font;

class UILayer
{
public:
	UILayer();
	virtual ~UILayer();

	void Init(int theWidth, int theHeight);
	void Destory();
	void Update(float delta);
	void Draw();

private:
	Font* mFont;
	int mWidth;
	int mHeight;

public:
	static UILayer&GetInstance()
	{
		static UILayer instance;
		return instance;
	}

};
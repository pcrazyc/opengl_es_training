#pragma once

#include <list>
#include "Shape.h"

class ShapeManager 
{
private:
	ShapeManager();
	~ShapeManager();

public:
	Shape* CreatShape(E_SHAPE_TYPE theType);
	void ClearAll();
	bool DeleteShape(Shape* theShape);
	void Update(float delta);
	void Draw();
	
private:
	bool AddToManager(Shape* theShape);
	bool IsInList(Shape* theShape);
	std::list<Shape*> mShapeList;

public:
	static ShapeManager&GetInstance()
	{
		static ShapeManager instance;
		return instance;
	}
};
#pragma once

#include "IwGL.h"
#include "ShapeManager.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Sphere.h"
#include "Cuboid.h"
#include "TestData.h"


ShapeManager::ShapeManager()
{

}

ShapeManager::~ShapeManager()
{
	ClearAll();
}

Shape* ShapeManager::CreatShape(E_SHAPE_TYPE theType)
{
	Shape* aShape = NULL;
	switch(theType)
	{
	case  	E_CUBE:
		aShape = new Cuboid(cubeX, cubeY, cubeZ );
		break;
	case	E_CUBOID:
		aShape = new Cuboid(cuboidX, cuboidY, cuboidZ);
		break;
	case 	E_CYLINDER:
		aShape = new Cylinder(cylinderRadius, cylinderHeight );
		break;
	case	E_SPHERE:
		aShape = new Sphere(sphereRadius);
		break;
	case 	E_CONE:
		aShape = new Cone(coneRadius, coneHeight );
		break;
	default:
		break;
	}
	AddToManager(aShape);
	return aShape;
}
 
void ShapeManager::ClearAll()
{
	std::list<Shape*>::iterator it = mShapeList.begin();
	for(; it!= mShapeList.end(); it++)
	{
		if(*it) {
			delete *it;
			*it = NULL;
		}
	}

	mShapeList.clear();
}

bool ShapeManager::AddToManager(Shape* theShape)
{
	if (!IsInList(theShape))
	{
		mShapeList.push_back(theShape);
		return true;
	}
	return false;
}

bool ShapeManager::DeleteShape(Shape* theShape)
{
	std::list<Shape*>::iterator it = mShapeList.begin();
	for(; it!= mShapeList.end(); it++)
	{
		if(*it == theShape)
		{
			mShapeList.erase(it);
			return true;
		}
	}
	return false;
}
void ShapeManager::Update(float delta)
{
	std::list<Shape*>::iterator it = mShapeList.begin();
	for(; it!= mShapeList.end(); it++)
	{
		Shape* aShape = *it;
		if (aShape)
		{
			aShape->Update();
		}
	}

}

void ShapeManager::Draw()
{
	std::list<Shape*>::iterator it = mShapeList.begin();
	for(; it!= mShapeList.end(); it++)
	{
		Shape* aShape = *it;
		if (aShape)
		{
			glPushMatrix();
			aShape->Draw();
			glPopMatrix();
		}
	}
}


bool ShapeManager::IsInList(Shape* theShape)
{
	std::list<Shape*>::iterator it = mShapeList.begin();
	for(; it!= mShapeList.end(); it++)
	{
		if(*it == theShape)
		{
			return true;
		}
	}
	return false;
}
#include "TestColor.h"
#include "stdio.h"

TestColor* TestColor::pSharedTestColor = NULL;

TestColor* TestColor::SharedTestColor() {
    if (pSharedTestColor == NULL) {
        pSharedTestColor = new TestColor();
        pSharedTestColor->InitColor();
    }

    return pSharedTestColor;
}

void TestColor::PurgeTestColor() {
    if (pSharedTestColor == NULL) return;

    delete pSharedTestColor;
    pSharedTestColor = NULL;
}

void TestColor::InitColor( float StepR/*=colorStepR*/, float stepG/*=colorStepG*/, float stepB/*=colorStepB*/, float r/*=0.0f*/, float g/*=0.0f*/, float b/*=0.0f*/ ) {
	mColorR = r;
	mColorG = g;
	mColorB = b;

	mColorStepR = StepR;
	mColorStepG = stepG;
	mColorStepB = stepB;
}

void TestColor::GetNextColor( float &r, float &g, float &b, float &a ) {
    mColorR += mColorStepR;
    mColorG += mColorStepG;
    mColorB += mColorStepB;

    mColorR = mColorR>1.0f ? (mColorR-1.0f) : mColorR;
    mColorG = mColorG>1.0f ? (mColorG-1.0f) : mColorG;
    mColorB = mColorB>1.0f ? (mColorB-1.0f) : mColorB;

    r = mColorR;
    g = mColorG;
    b = mColorB;
    a = 1.0f;
}
#pragma once

extern float colorStepR;
extern float colorStepG;
extern float colorStepB;

class TestColor {
public:
    static TestColor* SharedTestColor();
    static void PurgeTestColor();

    void InitColor(float StepR=colorStepR, float stepG=colorStepG, float stepB=colorStepB, float r=0.0f, float g=0.0f, float b=0.0f);
    void GetNextColor(float &r, float &g, float &b, float &a);
private:
    static TestColor* pSharedTestColor;

    float mColorR;
    float mColorG;
    float mColorB;

    float mColorStepR;
    float mColorStepG;
    float mColorStepB;
};
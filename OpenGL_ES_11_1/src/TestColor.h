#pragma once

class TestColor {
public:
    static TestColor* SharedTestColor();
    static void PurgeTestColor();

    void InitColor(float r=0.0f, float g=0.0f, float b=0.0f);
    void GetNextColor(float &r, float &g, float &b);
private:
    static TestColor* pSharedTestColor;

    float mColorR;
    float mColorG;
    float mColorB;

    float mColorStepR;
    float mColorStepG;
    float mColorStepB;
};
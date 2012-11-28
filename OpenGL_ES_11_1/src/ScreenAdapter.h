#pragma once

#define DEFAULT_WIDTH 480
#define DEFAULT_HEIGHT 320

class ScreenAdapter {
public:
    static ScreenAdapter* SharedScreenAdapter();
    static void PurgeScreenAdapter();

    ScreenAdapter();
    /*void PixelAdater(float &x);
    void PixelAdater(float *arrPixel, int n);*/


private:
    int mCurScreenWidth;
    int mCurScreenHeight;

    static ScreenAdapter *pSharedScreenAdapter;
};
#include "ScreenAdapter.h"
#include "IwGL.h"

ScreenAdapter* ScreenAdapter::pSharedScreenAdapter = NULL;

ScreenAdapter::ScreenAdapter(){
    mCurScreenWidth = IwGLGetInt(IW_GL_WIDTH);
    mCurScreenHeight = IwGLGetInt(IW_GL_HEIGHT);
}

ScreenAdapter* ScreenAdapter::SharedScreenAdapter() {
    if (pSharedScreenAdapter == NULL) {
        pSharedScreenAdapter = new ScreenAdapter();
    }

    return pSharedScreenAdapter;
}

void ScreenAdapter::PurgeScreenAdapter() {
    if (pSharedScreenAdapter == NULL) return;

    delete pSharedScreenAdapter;
    pSharedScreenAdapter = NULL;
}




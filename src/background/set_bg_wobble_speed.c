#include "types.h"
#include "background.h"

void SetBgWobbleSpeed(u32 bg, s32 speedX, s32 speedY)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.nSpeedX = speedX;
    pLayer->wobble.nSpeedY = speedY;
}

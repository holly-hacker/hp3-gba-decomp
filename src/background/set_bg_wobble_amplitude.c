#include "types.h"
#include "background.h"

void SetBgWobbleAmplitude(u32 bg, s32 ampX, s32 ampY)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.nAmpX = ampX;
    pLayer->wobble.nAmpY = ampY;
}

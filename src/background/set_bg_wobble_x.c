#include "types.h"
#include "background.h"

void SetBgWobbleX(u32 bg, s32 phase, s32 speed, s32 amplitude)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.wPhaseX = phase << 8;
    pLayer->wobble.nSpeedX = speed;
    pLayer->wobble.nAmpX = amplitude;
    pLayer->dwFlags |= BG_LAYER_WOBBLE;
}

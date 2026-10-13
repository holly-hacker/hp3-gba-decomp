#include "types.h"
#include "background.h"

void SetBgWobbleY(u32 bg, s32 phase, s32 speed, s32 amplitude)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.wPhaseY = phase << 8;
    pLayer->wobble.nSpeedY = speed;
    pLayer->wobble.nAmpY = amplitude;
    pLayer->dwFlags |= BG_LAYER_WOBBLE;
}

#include "types.h"
#include "background.h"

void SetBgWobblePhase(u32 bg, s32 phaseX, s32 phaseY)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.wPhaseX = phaseX << 8;
    pLayer->wobble.wPhaseY = phaseY << 8;
}

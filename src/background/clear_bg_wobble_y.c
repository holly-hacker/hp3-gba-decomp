#include "types.h"
#include "background.h"

void ClearBgWobbleY(u32 bg)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.wPhaseY = 0;
    pLayer->wobble.nSpeedY = 0;
    pLayer->wobble.nAmpY = 0;
}

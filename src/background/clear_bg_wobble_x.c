#include "types.h"
#include "background.h"

void ClearBgWobbleX(u32 bg)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble.wPhaseX = 0;
    pLayer->wobble.nSpeedX = 0;
    pLayer->wobble.nAmpX = 0;
}

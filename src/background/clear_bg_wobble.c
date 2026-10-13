#include "types.h"
#include "background.h"

void ClearBgWobble(u32 bg)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    ClearBgWobbleX(bg);
    ClearBgWobbleY(bg);
    pLayer->dwFlags &= ~BG_LAYER_WOBBLE;
}

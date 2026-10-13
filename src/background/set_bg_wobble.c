#include "types.h"
#include "background.h"

void SetBgWobble(u32 bg, const BgWobble *pWobble)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->wobble = *pWobble;
    pLayer->dwFlags |= BG_LAYER_WOBBLE;
}

#include "types.h"
#include "graphics/display.h"
#include "trig.h"

// Adds a sine offset to the layer's output scroll, one phase accumulator per axis.
void ApplyBgLayerWobble(u32 bg)
{
    BgLayer *pLayer;

    pLayer = &g_aBgLayers[bg];
    if (pLayer->nWobbleSpeedX != 0)
    {
        pLayer->wWobblePhaseX += pLayer->nWobbleSpeedX;
        pLayer->nOutX += g_anSineTable[(((s16)pLayer->wWobblePhaseX >> 8) + 0x40) & 0xFF] * pLayer->nWobbleAmpX;
    }

    if (pLayer->nWobbleSpeedY != 0)
    {
        pLayer->wWobblePhaseY += pLayer->nWobbleSpeedY;
        pLayer->nOutY += g_anSineTable[pLayer->wWobblePhaseY >> 8] * pLayer->nWobbleAmpY;
    }
}

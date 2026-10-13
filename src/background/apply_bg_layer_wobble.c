#include "types.h"
#include "background.h"
#include "math.h"

// Adds a sine offset to the layer's output scroll, one phase accumulator per axis.
void ApplyBgLayerWobble(u32 bg)
{
    BgLayer *pLayer;

    pLayer = &g_BgState.aLayers[bg];
    if (pLayer->wobble.nSpeedX != 0)
    {
        pLayer->wobble.wPhaseX += pLayer->wobble.nSpeedX;
        pLayer->out.x += g_anSineTable[(((s16)pLayer->wobble.wPhaseX >> 8) + 0x40) & 0xFF] * pLayer->wobble.nAmpX;
    }

    if (pLayer->wobble.nSpeedY != 0)
    {
        pLayer->wobble.wPhaseY += pLayer->wobble.nSpeedY;
        pLayer->out.y += g_anSineTable[pLayer->wobble.wPhaseY >> 8] * pLayer->wobble.nAmpY;
    }
}

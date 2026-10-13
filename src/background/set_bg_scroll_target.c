#include "types.h"
#include "background.h"

void SetBgScrollTarget(u32 bg, s32 x, s32 y, u32 frames)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->target.x = x;
    pLayer->target.y = y;
    pLayer->wTweenFrames = frames;
    pLayer->dwFlags |= BG_LAYER_TWEEN;
}

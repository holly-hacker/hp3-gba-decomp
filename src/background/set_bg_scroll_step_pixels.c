#include "types.h"
#include "background.h"

void SetBgScrollStepPixels(u32 bg, s32 x, s32 y)
{
    g_BgState.aLayers[bg].step.x = x << 16;
    g_BgState.aLayers[bg].step.y = y << 16;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_TWEEN;
}

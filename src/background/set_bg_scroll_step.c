#include "types.h"
#include "background.h"

void SetBgScrollStep(u32 bg, s32 x, s32 y)
{
    g_BgState.aLayers[bg].step.x = x;
    g_BgState.aLayers[bg].step.y = y;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_TWEEN;
}

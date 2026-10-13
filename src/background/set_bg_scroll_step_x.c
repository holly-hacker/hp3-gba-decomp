#include "types.h"
#include "background.h"

void SetBgScrollStepX(u32 bg, s32 x)
{
    g_BgState.aLayers[bg].step.x = x;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_TWEEN;
}

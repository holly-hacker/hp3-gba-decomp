#include "types.h"
#include "background.h"

void SetBgScrollStepY(u32 bg, s32 y)
{
    g_BgState.aLayers[bg].step.y = y;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_TWEEN;
}

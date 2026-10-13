#include "types.h"
#include "background.h"

void SetBgRotationCenter(u32 bg, s32 x, s32 y)
{
    g_BgState.aLayers[bg].nCenterX = x;
    g_BgState.aLayers[bg].nCenterY = y;
}

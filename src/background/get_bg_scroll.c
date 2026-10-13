#include "types.h"
#include "background.h"

void GetBgScroll(u32 bg, s32 *pX, s32 *pY)
{
    *pX = g_BgState.aLayers[bg].scroll.x;
    *pY = g_BgState.aLayers[bg].scroll.y;
}

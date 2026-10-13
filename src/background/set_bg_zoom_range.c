#include "types.h"
#include "background.h"

void SetBgZoomRange(u32 bg, s32 min, s32 max)
{
    g_BgState.aLayers[bg].nZoomMin = min;
    g_BgState.aLayers[bg].nZoomMax = max;
}

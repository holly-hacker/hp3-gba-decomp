#include "types.h"
#include "background.h"

void SetBgZoomStep(u32 bg, s32 step)
{
    g_BgState.aLayers[bg].nZoomStep = step;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_ZOOM_BOUNCE;
}

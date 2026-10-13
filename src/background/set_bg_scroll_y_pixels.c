#include "types.h"
#include "background.h"

void SetBgScrollYPixels(u32 bg, s32 y)
{
    g_BgState.aLayers[bg].scroll.y = y << 16;
    g_BgState.aLayers[bg].out.y = y << 16;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_COMMIT;
}

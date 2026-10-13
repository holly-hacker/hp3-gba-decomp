#include "types.h"
#include "background.h"

void SetBgScrollXPixels(u32 bg, s32 x)
{
    g_BgState.aLayers[bg].scroll.x = x << 16;
    g_BgState.aLayers[bg].out.x = x << 16;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_COMMIT;
}

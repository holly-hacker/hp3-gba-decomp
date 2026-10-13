#include "types.h"
#include "background.h"

void SetBgScrollFixed(u32 bg, s32 x, s32 y)
{
    g_BgState.aLayers[bg].scroll.x = x;
    g_BgState.aLayers[bg].scroll.y = y;
    g_BgState.aLayers[bg].out.x = x;
    g_BgState.aLayers[bg].out.y = y;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_COMMIT;
}

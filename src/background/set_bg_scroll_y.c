#include "types.h"
#include "background.h"

void SetBgScrollFixedY(u32 bg, s32 position)
{
    g_BgState.aLayers[bg].scroll.y = position;
    g_BgState.aLayers[bg].out.y = position;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_COMMIT;
}

#include "types.h"
#include "background.h"

void SetBgScrollFixedX(u32 bg, s32 position)
{
    g_BgState.aLayers[bg].scroll.x = position;
    g_BgState.aLayers[bg].out.x = position;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_COMMIT;
}

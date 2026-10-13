#include "types.h"
#include "background.h"

void SetBgZoom(u32 bg, u32 zoom)
{
    g_BgState.aLayers[bg].wZoom = zoom;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_MATRIX_DIRTY;
}

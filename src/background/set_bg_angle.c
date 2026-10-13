#include "types.h"
#include "background.h"

void SetBgAngle(u32 bg, u32 angle)
{
    g_BgState.aLayers[bg].wAngle = angle;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_MATRIX_DIRTY;
}

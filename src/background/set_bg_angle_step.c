#include "types.h"
#include "background.h"

void SetBgAngleStep(u32 bg, u32 step)
{
    g_BgState.aLayers[bg].wAngleStep = step;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_ROTATE;
}

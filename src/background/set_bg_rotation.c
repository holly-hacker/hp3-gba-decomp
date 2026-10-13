#include "types.h"
#include "background.h"

void SetBgRotation(u32 bg, u32 angle, u32 step)
{
    g_BgState.aLayers[bg].wAngle = angle;
    g_BgState.aLayers[bg].wAngleStep = step;
    g_BgState.aLayers[bg].dwFlags |= BG_LAYER_ROTATE;
}

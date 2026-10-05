#include "types.h"
#include "graphics/graphics.h"
#include "graphics/oam.h"

void InitOamSystem(void)
{
    g_pOamShadowBuffer = g_aOamShadowBufferA;
    ClearOamShadowBuffers();
    ResetAffineSlots();
    g_pOamDmaShadowBuffer = g_aOamShadowBufferB;
}

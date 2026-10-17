#include "types.h"
#include "graphics/graphics.h"
#include "hw/bios.h"

void CommitObjAffineMatrices(void)
{
    if (g_bAffineSlotHighWaterMark != 0) {
        bios_ObjAffineSet(g_aObjAffineSetSource, &g_pOamShadowBuffer->aHalves[0][0].affineParam, g_bAffineSlotHighWaterMark, 8);
        bios_ObjAffineSet(g_aObjAffineSetSource, &g_pOamShadowBuffer->aHalves[1][0].affineParam, g_bAffineSlotHighWaterMark, 8);
    }
}

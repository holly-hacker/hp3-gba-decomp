#include "types.h"
#include "object.h"
#include "mem.h"

// Drops the object's hold on its sprite VRAM tiles. An object sharing tiles
// through its pool aux record frees them only when the last user releases
// them; one that owns its tiles frees them directly, variant slots included.
void ReleaseObjectOffscreenVramTiles(Object *obj)
{
    ObjectVariantSlot *variantSlot;
    u32 auxSlot;
    u32 index;
    s32 i;

    if (obj->dwFlags & ObjectFlagSkipSpriteFrameUpdate)
        return;

    if (obj->bDrawFlags & (ObjectDrawFlagShareTiles | ObjectDrawFlagShareFrameTiles)) {
        if (obj->wVramTileAllocId != 0xFFFF) {
            auxSlot = obj->bObjectPoolAuxSlot;
            if (obj->bDrawFlags & ObjectDrawFlagShareTiles)
                index = 0;
            else
                index = obj->bAnimFrameIndex_candidate;

            if (--g_pObjectPoolAuxBuffer[auxSlot].abRefCounts[index] == 0) {
                g_pObjectPoolAuxBuffer[auxSlot].awTileAllocIds[index] = 0xFFFF;
                FreeObjectVramTileAllocation(obj->wVramTileAllocId, obj->wVramTileRow,
                                             obj->bLargeSprite_candidate);
            }

            obj->wVramTileAllocId = 0xFFFF;
            obj->wVramTileRow = 0;
        }
    }
    else {
        if (obj->wVramTileAllocId != 0xFFFF) {
            FreeObjectVramTileAllocation(obj->wVramTileAllocId, obj->wVramTileRow,
                                         obj->bLargeSprite_candidate);
            obj->wVramTileAllocId = 0xFFFF;
            obj->wVramTileRow = 0;
        }

        if (obj->bDrawFlags & ObjectDrawFlagVariantSlots) {
            for (i = 0; i < 1; i++) {
                variantSlot = &obj->aVariantSlots[i];
                if (variantSlot->wVramTileAllocId != 0xFFFF) {
                    FreeObjectVramTileAllocation(variantSlot->wVramTileAllocId, variantSlot->wVramTileRow,
                                                 obj->bLargeSprite_candidate);
                    variantSlot->wVramTileAllocId = 0xFFFF;
                    variantSlot->wVramTileRow = 0;
                }
            }
        }
    }
}

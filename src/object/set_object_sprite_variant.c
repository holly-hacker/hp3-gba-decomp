#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "object.h"

void SetObjectSpriteVariant(Object *obj, s8 tableIndex, s8 variantIndex)
{
    ObjectAssetRecord *record;
    void *palette;

    record = &obj->aVariantSlots[0].pSpriteVariantTables[tableIndex][variantIndex];
    obj->aVariantSlots[0].bSpriteVariantIndex = variantIndex;
    obj->aVariantSlots[0].bSpriteVariantTableIndex = tableIndex;
    obj->bAnimFrameDelay = record->bAnimFrameDelay;
    SetObjectAssetRecord(obj, record);

    palette = record->pPalette;
    if (palette != 0) {
        if (g_dwGameModeFlags & 0x10)
            sub_0800D254(palette, obj->bGfxSlotAndFlags >> 4 << 4, 0x10);
        else
            sub_0800D264(palette, obj->bGfxSlotAndFlags >> 4 << 4, 0x10);
    }
}

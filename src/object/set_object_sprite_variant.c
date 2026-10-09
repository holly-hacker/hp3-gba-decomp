#include "types.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/object.h"

void SetObjectSpriteVariant(Object *obj, s8 tableIndex, s8 variantIndex)
{
    ObjectAssetRecord *record;
    const ObjPalette *palette;

    record = &obj->aVariantSlots[0].pSpriteVariantTables[tableIndex][variantIndex];
    obj->bSpriteVariantIndex = variantIndex;
    obj->bSpriteVariantTableIndex = tableIndex;
    obj->anim.bAnimFrameDelay = record->bAnimFrameDelay;
    SetObjectAssetRecord(obj, record);

    palette = record->pPalette;
    if (palette != 0) {
        if (g_dwGameModeFlags & 0x10)
            sub_0800D254(palette->aColors, obj->oam.paletteNum << 4, 0x10);
        else
            QueueObjPaletteLoad(palette->aColors, obj->oam.paletteNum << 4, 0x10);
    }
}

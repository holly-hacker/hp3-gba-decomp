#include "types.h"
#include "color.h"
#include "actor.h"
#include "main.h"

void SetActorSpriteVariant(Actor *actor, s8 tableIndex, s8 variantIndex)
{
    ActorAssetRecord *record;
    const ObjPalette *palette;

    record = &actor->aVariantSlots[0].pSpriteVariantTables[tableIndex][variantIndex];
    actor->bSpriteVariantIndex = variantIndex;
    actor->bSpriteVariantTableIndex = tableIndex;
    actor->anim.bAnimFrameDelay = record->bAnimFrameDelay;
    SetActorAssetRecord(actor, record);

    palette = record->pPalette;
    if (palette != 0) {
        if (g_dwGameModeFlags & 0x10)
            sub_0800D254(palette->aColors, actor->oam.paletteNum << 4, 0x10);
        else
            QueueObjPaletteLoad(palette->aColors, actor->oam.paletteNum << 4, 0x10);
    }
}

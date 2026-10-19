#include "color.h"
#include "actor.h"
#include "main.h"

// Applies an ActorAssetRecord: its frame delay, its tiles and frames, and its
// palette (when it has one) in the actor's OBJ palette bank.
void SetActorSprite(Actor *actor, const void *pRecord)
{
    const ActorAssetRecord *record;
    const ObjPalette *palette;

    record = pRecord;
    actor->anim.bAnimFrameDelay = record->bAnimFrameDelay;
    SetActorAssetRecord(actor, record);

    palette = record->pPalette;
    if (palette != 0) {
        if (g_dwGameModeFlags & 0x10)
            LoadObjPaletteColors(palette->aColors, actor->oam.paletteNum << 4, 0x10);
        else
            QueueObjPaletteLoad(palette->aColors, actor->oam.paletteNum << 4, 0x10);
    }
}

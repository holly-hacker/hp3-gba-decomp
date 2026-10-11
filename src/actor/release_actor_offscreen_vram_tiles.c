#include "types.h"
#include "actor.h"
#include "hw/mem.h"
#include "vram.h"

// Drops the actor's hold on its sprite VRAM tiles. An actor sharing tiles
// through its pool aux record frees them only when the last user releases
// them; one that owns its tiles frees them directly, variant slots included.
void ReleaseActorOffscreenVramTiles(Actor *actor)
{
    ActorVariantSlot *variantSlot;
    u32 auxSlot;
    u32 index;
    s32 i;

    if (actor->dwFlags & ActorFlagSkipSpriteFrameUpdate)
        return;

    if (actor->bDrawFlags & (ActorDrawFlagShareTiles | ActorDrawFlagShareFrameTiles)) {
        if (actor->wVramTileAllocId != 0xFFFF) {
            auxSlot = actor->bActorPoolAuxSlot;
            if (actor->bDrawFlags & ActorDrawFlagShareTiles)
                index = 0;
            else
                index = actor->anim.bAnimFrameIndex_candidate;

            if (--g_pActorPoolAuxBuffer[auxSlot].abRefCounts[index] == 0) {
                g_pActorPoolAuxBuffer[auxSlot].awTileAllocIds[index] = 0xFFFF;
                FreeObjVramTileAllocation(actor->wVramTileAllocId, actor->wVramPixelCount,
                                             actor->oam.bpp8);
            }

            actor->wVramTileAllocId = 0xFFFF;
            actor->wVramPixelCount = 0;
        }
    }
    else {
        if (actor->wVramTileAllocId != 0xFFFF) {
            FreeObjVramTileAllocation(actor->wVramTileAllocId, actor->wVramPixelCount,
                                         actor->oam.bpp8);
            actor->wVramTileAllocId = 0xFFFF;
            actor->wVramPixelCount = 0;
        }

        if (actor->bDrawFlags & ActorDrawFlagVariantSlots) {
            for (i = 0; i < ARRAY_COUNT(actor->aVariantSlots); i++) {
                variantSlot = &actor->aVariantSlots[i];
                if (variantSlot->wVramTileAllocId != 0xFFFF) {
                    FreeObjVramTileAllocation(variantSlot->wVramTileAllocId, variantSlot->wVramPixelCount,
                                                 actor->oam.bpp8);
                    variantSlot->wVramTileAllocId = 0xFFFF;
                    variantSlot->wVramPixelCount = 0;
                }
            }
        }
    }
}

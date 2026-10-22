#include "types.h"
#include "actor.h"

// Returns the tile graphics of a variant slot's current animation frame:
// the variant's pTileGfx plus the frame's wTileGfxOffset. The frame is
// selected as in GetActorVariantFrameSize.
void *GetActorVariantFrameTileGfx(Actor *actor, u8 slot)
{
    u8 tableIndex;
    u8 variantIndex;
    ActorAssetRecord *record;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    u32 wrap;
    s32 frame;

    tableIndex = actor->bSpriteVariantTableIndex;
    variantIndex = actor->bSpriteVariantIndex;
    record = &actor->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex];
    frameData = record->pFrameData;

    wrap = actor->aVariantSlots[slot].bFrameFlags & ActorVariantSlotFlagPrevFrameWrap;
    if (wrap || (actor->aVariantSlots[slot].bFrameFlags & ActorVariantSlotFlagPrevFrameClamp)) {
        frame = actor->anim.bLastAnimFrameValue - 1;
        if (frame < 0) {
            if (wrap)
                frame = frameData->wFrameCount - 1;
            else
                frame = 0;
        }
    }
    else {
        frame = actor->anim.bLastAnimFrameValue;
    }

    frameDesc = ACTOR_FRAME_DESC(frameData, frame);
    return (u8 *)record->pTileGfx + frameDesc->wTileGfxOffset;
}

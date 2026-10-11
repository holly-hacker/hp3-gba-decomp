#include "types.h"
#include "actor.h"

// Writes the pixel width and height of a variant slot's current animation
// frame to dims[0] and dims[1]. UpdateActorSpriteFrame sizes the slot's VRAM
// tile allocation from their product. Flag bits 0x4/0x8 select the frame
// before bLastAnimFrameValue, wrapping (0x4) or clamping (0x8) below frame 0.
void GetActorVariantFrameSize(Actor *actor, u32 *dims, u8 slot)
{
    s32 tableIndex;
    s32 variantIndex;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    u32 wrap;
    s32 frame;

    tableIndex = actor->bSpriteVariantTableIndex;
    variantIndex = actor->bSpriteVariantIndex;
    frameData = actor->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;

    wrap = actor->aVariantSlots[slot].bFrameFlags & 4;
    if (wrap || (actor->aVariantSlots[slot].bFrameFlags & 8)) {
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

    frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[frame]);
    dims[0] = frameDesc->bWidth;
    dims[1] = frameDesc->bHeight;
}

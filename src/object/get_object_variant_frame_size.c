#include "types.h"
#include "object.h"

// Writes the pixel width and height of a variant slot's current animation
// frame to dims[0] and dims[1]. UpdateObjectSpriteFrame sizes the slot's VRAM
// tile allocation from their product. Flag bits 0x4/0x8 select the frame
// before bLastAnimFrameValue, wrapping (0x4) or clamping (0x8) below frame 0.
void GetObjectVariantFrameSize(Object *obj, u32 *dims, u8 slot)
{
    s32 tableIndex;
    s32 variantIndex;
    ObjectFrameData *frameData;
    ObjectFrameDesc *frameDesc;
    u32 wrap;
    s32 frame;

    tableIndex = obj->bSpriteVariantTableIndex;
    variantIndex = obj->bSpriteVariantIndex;
    frameData = obj->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;

    wrap = obj->aVariantSlots[slot].bFrameFlags & 4;
    if (wrap || (obj->aVariantSlots[slot].bFrameFlags & 8)) {
        frame = obj->bLastAnimFrameValue - 1;
        if (frame < 0) {
            if (wrap)
                frame = frameData->wFrameCount - 1;
            else
                frame = 0;
        }
    }
    else {
        frame = obj->bLastAnimFrameValue;
    }

    frameDesc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[frame]);
    dims[0] = frameDesc->bWidth;
    dims[1] = frameDesc->bHeight;
}

#include "types.h"
#include "object.h"

// Returns the tile graphics of a variant slot's current animation frame:
// the variant's pTileGfx plus the frame's wTileGfxOffset. The frame is
// selected as in GetObjectVariantFrameSize.
void *GetObjectVariantFrameTileGfx(Object *obj, u8 slot)
{
    u8 tableIndex;
    u8 variantIndex;
    ObjectAssetRecord *record;
    ObjectFrameData *frameData;
    ObjectFrameDesc *frameDesc;
    u32 wrap;
    s32 frame;

    tableIndex = obj->bSpriteVariantTableIndex;
    variantIndex = obj->bSpriteVariantIndex;
    record = &obj->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex];
    frameData = record->pFrameData;

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
    return (u8 *)record->pTileGfx + frameDesc->wTileGfxOffset;
}

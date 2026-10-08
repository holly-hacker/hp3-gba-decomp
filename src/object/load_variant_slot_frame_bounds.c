#include "graphics/object.h"

// LoadObjectAnimFrameBounds for objects drawn from variant slots: a slot with
// ObjectVariantSlotFlagBounds supplies the terrain box, collision boxes and (slot
// 0 only) sprite bounds from its own current frame. Only the slot frame's boxes
// with a nonzero state are copied.
void LoadVariantSlotFrameBounds(Object *obj)
{
    u8 i;
    u8 tableIndex;
    u8 variantIndex;
    ObjectFrameData *frameData;
    ObjectFrameDesc *frameDesc;
    s16 *origin;
    s8 *box;
    u32 wrap;
    s32 frame;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(obj->aVariantSlots); i++) {
        if (obj->aVariantSlots[i].pSpriteVariantTables == NULL)
            continue;
        if (!(obj->aVariantSlots[i].bFrameFlags & ObjectVariantSlotFlagBounds))
            continue;

        variantIndex = obj->bSpriteVariantIndex;
        tableIndex = obj->bSpriteVariantTableIndex;
        frameData = obj->aVariantSlots[i].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;

        obj->bTerrainBoxLeft = frameData->abTerrainBox[0];
        obj->bTerrainBoxRight = frameData->abTerrainBox[1];
        obj->bTerrainBoxTop = frameData->abTerrainBox[2];
        obj->bTerrainBoxBottom = frameData->abTerrainBox[3];

        wrap = obj->aVariantSlots[i].bFrameFlags & ObjectVariantSlotFlagPrevFrameWrap;
        if (wrap || (obj->aVariantSlots[i].bFrameFlags & ObjectVariantSlotFlagPrevFrameClamp)) {
            frame = obj->anim.bLastAnimFrameValue - 1;
            if (frame < 0) {
                if (wrap)
                    frame = frameData->wFrameCount - 1;
                else
                    frame = 0;
            }
        }
        else {
            frame = obj->anim.bLastAnimFrameValue;
        }

        frameDesc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[frame]);

        if (i == 0) {
            origin = frameDesc->awOrigin;
            obj->spriteBounds.edges.wLeft = origin[0];
            obj->spriteBounds.edges.wRight = origin[0] + frameDesc->bWidth;
            obj->spriteBounds.edges.wTop = origin[1];
            obj->spriteBounds.edges.wBottom = origin[1] + frameDesc->bHeight;
        }

        box = (s8 *)frameDesc + (frameData->bFrameHeaderExtra * 2 + 10);
        for (j = 0; j < frameData->bFramePartCount; j++) {
            if (box[j * 6 + 4] != 0) {
                obj->aCollisionBoxes[j].offsets.edges.bLeft = box[j * 6 + 0];
                obj->aCollisionBoxes[j].offsets.edges.bTop = box[j * 6 + 2];
                obj->aCollisionBoxes[j].offsets.edges.bRight = box[j * 6 + 1];
                obj->aCollisionBoxes[j].offsets.edges.bBottom = box[j * 6 + 3];
                obj->aCollisionBoxes[j].state.bState = box[j * 6 + 4];
                if (obj->bCollisionBoxCount <= j)
                    obj->bCollisionBoxCount++;
            }
        }
    }
}

#include "graphics/object.h"

// Copies the current animation frame's terrain box, sprite bounds and collision
// boxes into the object, unless that frame is already loaded, and flags its
// tiles for upload.
void LoadObjectAnimFrameBounds(Object *obj)
{
    ObjectAnimState *anim;
    ObjectFrameData *frameData;
    ObjectFrameDesc *frameDesc;
    s16 *origin;
    u8 *box;
    s32 i;

    anim = &obj->anim;
    if (anim->bAnimFrameIndex_candidate == anim->bLastAnimFrameValue
        && !(obj->dwFlags & ObjectFlagAnimFrameLoaded))
        return;

    frameData = anim->pAnimTable->pFrameData;
    if (frameData != NULL) {
        frameDesc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets
                                        + frameData->awFrameOffsets[anim->bLastAnimFrameValue]);
        origin = frameDesc->awOrigin;

        obj->bTerrainBoxLeft = frameData->abTerrainBox[0];
        obj->bTerrainBoxRight = frameData->abTerrainBox[1];
        obj->bTerrainBoxTop = frameData->abTerrainBox[2];
        obj->bTerrainBoxBottom = frameData->abTerrainBox[3];

        obj->spriteBounds.edges.wLeft = origin[0];
        obj->spriteBounds.edges.wRight = origin[0] + frameDesc->bWidth;
        obj->spriteBounds.edges.wTop = origin[1];
        obj->spriteBounds.edges.wBottom = origin[1] + frameDesc->bHeight;

        box = (u8 *)frameDesc + (frameData->bFrameHeaderExtra * 2 + 10);
        for (i = 0; i < frameData->bFramePartCount; i++) {
            obj->aCollisionBoxes[i].offsets.edges.bLeft = box[i * 6 + 0];
            obj->aCollisionBoxes[i].offsets.edges.bTop = box[i * 6 + 2];
            obj->aCollisionBoxes[i].offsets.edges.bRight = box[i * 6 + 1];
            obj->aCollisionBoxes[i].offsets.edges.bBottom = box[i * 6 + 3];
            obj->aCollisionBoxes[i].state.bState = box[i * 6 + 4];
        }

        for (i = frameData->bFramePartCount; i < ARRAY_COUNT(obj->aCollisionBoxes); i++)
            obj->aCollisionBoxes[i].state.bState = 0;

        obj->bCollisionBoxCount = frameData->bFramePartCount;
    }

    if (obj->bDrawFlags & ObjectDrawFlagVariantSlots)
        LoadVariantSlotFrameBounds(obj);

    obj->dwFlags |= ObjectFlagAnimFrameLoaded;
}

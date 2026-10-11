#include "actor.h"

// LoadActorAnimFrameBounds for actors drawn from variant slots: a slot with
// ActorVariantSlotFlagBounds supplies the terrain box, collision boxes and (slot
// 0 only) sprite bounds from its own current frame. Only the slot frame's boxes
// with a nonzero state are copied.
void LoadVariantSlotFrameBounds(Actor *actor)
{
    u8 i;
    u8 tableIndex;
    u8 variantIndex;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    s16 *origin;
    s8 *box;
    u32 wrap;
    s32 frame;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(actor->aVariantSlots); i++) {
        if (actor->aVariantSlots[i].pSpriteVariantTables == NULL)
            continue;
        if (!(actor->aVariantSlots[i].bFrameFlags & ActorVariantSlotFlagBounds))
            continue;

        variantIndex = actor->bSpriteVariantIndex;
        tableIndex = actor->bSpriteVariantTableIndex;
        frameData = actor->aVariantSlots[i].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;

        actor->bTerrainBoxLeft = frameData->abTerrainBox[0];
        actor->bTerrainBoxRight = frameData->abTerrainBox[1];
        actor->bTerrainBoxTop = frameData->abTerrainBox[2];
        actor->bTerrainBoxBottom = frameData->abTerrainBox[3];

        wrap = actor->aVariantSlots[i].bFrameFlags & ActorVariantSlotFlagPrevFrameWrap;
        if (wrap || (actor->aVariantSlots[i].bFrameFlags & ActorVariantSlotFlagPrevFrameClamp)) {
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

        if (i == 0) {
            origin = frameDesc->awOrigin;
            actor->spriteBounds.edges.wLeft = origin[0];
            actor->spriteBounds.edges.wRight = origin[0] + frameDesc->bWidth;
            actor->spriteBounds.edges.wTop = origin[1];
            actor->spriteBounds.edges.wBottom = origin[1] + frameDesc->bHeight;
        }

        box = (s8 *)frameDesc + (frameData->bAnchorCount * 2 + 10);
        for (j = 0; j < frameData->bFramePartCount; j++) {
            if (box[j * 6 + 4] != 0) {
                actor->aCollisionBoxes[j].offsets.edges.bLeft = box[j * 6 + 0];
                actor->aCollisionBoxes[j].offsets.edges.bTop = box[j * 6 + 2];
                actor->aCollisionBoxes[j].offsets.edges.bRight = box[j * 6 + 1];
                actor->aCollisionBoxes[j].offsets.edges.bBottom = box[j * 6 + 3];
                actor->aCollisionBoxes[j].state.bState = box[j * 6 + 4];
                if (actor->bCollisionBoxCount <= j)
                    actor->bCollisionBoxCount++;
            }
        }
    }
}

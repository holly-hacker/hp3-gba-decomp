#include "actor.h"

// Copies the current animation frame's terrain box, sprite bounds and collision
// boxes into the actor, unless that frame is already loaded, and flags its
// tiles for upload.
void LoadActorAnimFrameBounds(Actor *actor)
{
    ActorAnimState *anim;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    s16 *origin;
    u8 *box;
    s32 i;

    anim = &actor->anim;
    if (anim->bAnimFrameIndex_candidate == anim->bLastAnimFrameValue
        && !(actor->dwFlags & ActorFlagAnimFrameLoaded))
        return;

    frameData = anim->pAnimTable->pFrameData;
    if (frameData != NULL) {
        frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets
                                        + frameData->awFrameOffsets[anim->bLastAnimFrameValue]);
        origin = frameDesc->awOrigin;

        actor->bTerrainBoxLeft = frameData->abTerrainBox[0];
        actor->bTerrainBoxRight = frameData->abTerrainBox[1];
        actor->bTerrainBoxTop = frameData->abTerrainBox[2];
        actor->bTerrainBoxBottom = frameData->abTerrainBox[3];

        actor->spriteBounds.edges.wLeft = origin[0];
        actor->spriteBounds.edges.wRight = origin[0] + frameDesc->bWidth;
        actor->spriteBounds.edges.wTop = origin[1];
        actor->spriteBounds.edges.wBottom = origin[1] + frameDesc->bHeight;

        box = (u8 *)frameDesc + (frameData->bAnchorCount * 2 + 10);
        for (i = 0; i < frameData->bFramePartCount; i++) {
            actor->aCollisionBoxes[i].offsets.edges.bLeft = box[i * 6 + 0];
            actor->aCollisionBoxes[i].offsets.edges.bTop = box[i * 6 + 2];
            actor->aCollisionBoxes[i].offsets.edges.bRight = box[i * 6 + 1];
            actor->aCollisionBoxes[i].offsets.edges.bBottom = box[i * 6 + 3];
            actor->aCollisionBoxes[i].state.bState = box[i * 6 + 4];
        }

        for (i = frameData->bFramePartCount; i < ARRAY_COUNT(actor->aCollisionBoxes); i++)
            actor->aCollisionBoxes[i].state.bState = 0;

        actor->bCollisionBoxCount = frameData->bFramePartCount;
    }

    if (actor->bDrawFlags & ActorDrawFlagVariantSlots)
        LoadVariantSlotFrameBounds(actor);

    actor->dwFlags |= ActorFlagAnimFrameLoaded;
}

#include "actor.h"

// Returns the tile graphics of the actor's current animation frame.
void *GetActorFrameTileGfx(Actor *actor)
{
    ActorAssetRecord *record;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;

    record = actor->anim.pAnimTable;
    frameData = record->pFrameData;
    frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets
                                   + frameData->awFrameOffsets[actor->anim.bLastAnimFrameValue]);
    return (u8 *)record->pTileGfx + frameDesc->wTileGfxOffset;
}

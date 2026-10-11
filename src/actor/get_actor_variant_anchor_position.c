#include "actor.h"

// GetActorAnchorPosition for the frames of a variant slot's sprite, selected
// by bAnimSet_candidate and bSpriteVariantIndex.
s32 GetActorVariantAnchorPosition(Actor *actor, u8 slot, u8 index, IntPoint *out)
{
    u32 lastRightFacing;

    lastRightFacing = (actor->dwFlags & ActorFlagSixteenWayDirections) ? 8 : DirectionDown;

    if (GetActorFrameAnchor(actor,
                            actor->aVariantSlots[slot].pSpriteVariantTables[actor->bAnimSet_candidate]
                                [actor->bSpriteVariantIndex].pFrameData,
                            index, out) == 1) {
        out->y = actor->pos.y + (out->y << 16);
        if (actor->bFacing > lastRightFacing)
            out->x = actor->pos.x - (out->x << 16);
        else
            out->x = actor->pos.x + (out->x << 16);
        return 1;
    }

    return 0;
}

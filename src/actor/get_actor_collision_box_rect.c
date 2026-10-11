#include "types.h"
#include "actor.h"

// Returns collision box boxIndex as pixel edges around the actor's
// previous-frame position, mirrored by its flip bits.
ActorRect GetActorCollisionBoxRect(Actor *actor, s32 boxIndex)
{
    ActorRect rect;
    s32 offsets;
    s32 origin;

    offsets = (actor->aCollisionBoxes + boxIndex)->offsets.dwPackedOffsets;

    origin = (s16)(actor->posPrev.y >> 16);
    if (actor->oam.vFlip) {
        rect.top = origin - (offsets >> 24);
        offsets <<= 8;
        rect.bottom = origin - (offsets >> 24);
    }
    else {
        rect.bottom = origin + (offsets >> 24);
        offsets <<= 8;
        rect.top = origin + (offsets >> 24);
    }
    offsets <<= 8;

    origin = (s16)(actor->posPrev.x >> 16);
    if (actor->oam.hFlip) {
        rect.left = origin - (offsets >> 24);
        offsets <<= 8;
        rect.right = origin - (offsets >> 24);
    }
    else {
        rect.right = origin + (offsets >> 24);
        offsets <<= 8;
        rect.left = origin + (offsets >> 24);
    }

    return rect;
}

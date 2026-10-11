#include "actor.h"

s32 IsActorFlippedX(Actor *actor)
{
    if (actor->oam.affineMode == 0)
        return actor->oam.hFlip ? 1 : 0;
    return (u32)actor->nAffineScaleX >> 31;
}

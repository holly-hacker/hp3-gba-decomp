#include "actor.h"

s32 IsActorFlippedY(Actor *actor)
{
    if (actor->oam.affineMode == 0)
        return actor->oam.vFlip ? 1 : 0;
    return (u32)actor->nAffineScaleY >> 31;
}

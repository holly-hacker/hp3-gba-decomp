#include "types.h"
#include "actor.h"
#include "combat_fighter.h"

// Bobs a floating damage number with a shrinking bounce: wTimedMoveTicks
// counts the bounces left, dwStateTimer the frames of the current one.
void TickFloatingDamageNumber(Actor *actor)
{
    if (--actor->dwStateTimer != 0)
        return;

    if (--actor->wTimedMoveTicks == 0)
    {
        actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
    }
    else
    {
        SetActorOrbitY(actor, 0x76, 0xA00, 12 / ((3 - actor->wTimedMoveTicks) * 2));
        actor->dwStateTimer = 24 / ((3 - actor->wTimedMoveTicks) * 2);
    }
}

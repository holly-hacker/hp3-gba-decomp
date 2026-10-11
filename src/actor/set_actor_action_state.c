#include "types.h"
#include "actor.h"

// No-op if already in the requested state; otherwise sets it and raises
// bActionFlags bit 0x01, the generic "action state just changed" flag each
// actor type's own tick function checks on its next tick (e.g.
// TickFighterAttackAnimState_candidate for battle fighters,
// TickObjectActionState_candidate and TickWanderingMonsterObject elsewhere).
void SetActorActionState(Actor *actor, u8 state)
{
    if (actor->bActionState != state)
    {
        actor->bActionState = state;
        actor->bActionFlags |= 1;
    }
}

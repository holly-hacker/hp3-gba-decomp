#include "types.h"
#include "battle.h"

// No-op if already in the requested state; otherwise sets it and raises the
// generic "action state just changed" flag TickPlayerActionState/
// TickFighterAttackAnimState_candidate check for on their next tick.
void SetFighterAttackAnimState_candidate(Object *obj, u8 state)
{
    if (obj->bActionState != state)
    {
        obj->bActionState = state;
        obj->bActionFlags |= 1;
    }
}

#include "types.h"
#include "object.h"

// No-op if already in the requested state; otherwise sets it and raises
// bActionFlags bit 0x01, the generic "action state just changed" flag each
// object type's own tick function checks on its next tick (e.g.
// TickFighterAttackAnimState_candidate for battle fighters,
// TickObjectActionState_candidate and TickWanderingMonsterObject elsewhere).
void SetObjectActionState(Object *obj, u8 state)
{
    if (obj->bActionState != state)
    {
        obj->bActionState = state;
        obj->bActionFlags |= 1;
    }
}

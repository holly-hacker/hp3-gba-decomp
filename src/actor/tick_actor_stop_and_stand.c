#include "actor.h"
#include "hero.h"

// Action state 3: stops and stands, then returns to action state 0.
void TickActorStopAndStand(Actor *actor)
{
    CancelActorMove_candidate(actor);
    SetPartyMemberAnim(actor, PartyAnimStand);
    SetActorActionState(actor, 0);
    SetActorActionSubState(actor, 2);
}

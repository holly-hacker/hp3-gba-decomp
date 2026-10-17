#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "hero.h"

// Action state 0x24, held during dialog: stops and stands.
void TickActorInDialog(Actor *actor)
{
    CancelActorMove_candidate(actor);
    SetPartyMemberAnim(actor, PartyAnimStand);
}

#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"

// Action state 0x24, held during dialogue: stops and stands.
void TickActorInDialogue(Actor *actor)
{
    CancelActorMove_candidate(actor);
    SetPartyMemberAnim(actor, PartyAnimStand);
}

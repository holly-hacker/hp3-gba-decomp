#include "actor.h"
#include "hero.h"
#include "overworld/overworld.h"

void StartFieldSpellCast(Actor *actor)
{
    CancelActorMove_candidate(actor);
    SetActorActionSubState(actor, 0);
    SetActorActionState(actor, 0x13);
    actor->bFighterIndex = g_aFieldSpells[g_bSelectedFieldSpell].dwSpell;
    actor->posPrev = actor->pos;
}

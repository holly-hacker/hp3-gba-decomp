#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "hero.h"

// Action state 0x13: plays the cast animation, then spawns the effect of the field
// spell in bFighterIndex on the animation event and returns to bPrevActionState_candidate
// once the animation ends.
void TickActorCastFieldSpell(Actor *actor)
{
    switch (actor->bActionSubState) {
    case 0:
        SetPartyMemberAnim(actor, PartyAnimCast);
        SetActorActionSubState(actor, 8);
        break;
    case 8:
        if (actor->dwFlags & ActorFlagAnimPaused) {
            SetActorActionState(actor, actor->bPrevActionState_candidate);
            SetActorActionSubState(actor, 2);
            SetPartyMemberAnim(actor, PartyAnimStand);
        }
        else if (actor->dwFlags & ActorFlagSpecialMoveTrigger) {
            actor->dwFlags &= ~ActorFlagSpecialMoveTrigger;
            switch (actor->bFighterIndex) {
            case 0:
                SpawnFieldSpellEffect_candidate(actor, 0);
                break;
            case 1:
                SpawnFieldSpellEffect_candidate(actor, 1);
                break;
            case 2:
                SpawnFieldSpellEffect_candidate(actor, 2);
                break;
            case 3:
                SpawnFieldSpellEffect_candidate(actor, 3);
                break;
            case 4:
                SpawnFieldSpellEffect_candidate(actor, 4);
                break;
            case 5:
                SpawnFieldSpellEffect_candidate(actor, 5);
                break;
            case 6:
                SpawnFieldSpellEffect_candidate(actor, 6);
                break;
            case 7:
                SpawnFieldSpellEffect_candidate(actor, 7);
                break;
            }
        }
        else if (actor->dwFlags & ActorFlagActionAnimDone) {
            actor->dwFlags &= ~ActorFlagActionAnimDone;
            SetActorActionState(actor, actor->bPrevActionState_candidate);
            SetActorActionSubState(actor, 2);
            SetPartyMemberAnim(actor, PartyAnimStand);
        }
        break;
    }
}

#include "actor.h"
#include "hero.h"
#include "move.h"

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
            case FieldSpellFlipendo:
                SpawnFieldSpellEffect(actor, FieldSpellFlipendo);
                break;
            case FieldSpellLumos:
                SpawnFieldSpellEffect(actor, FieldSpellLumos);
                break;
            case FieldSpellReparo:
                SpawnFieldSpellEffect(actor, FieldSpellReparo);
                break;
            case FieldSpellAlohomora:
                SpawnFieldSpellEffect(actor, FieldSpellAlohomora);
                break;
            case FieldSpellGlacius:
                SpawnFieldSpellEffect(actor, FieldSpellGlacius);
                break;
            case FieldSpellSpongify:
                SpawnFieldSpellEffect(actor, FieldSpellSpongify);
                break;
            case FieldSpellDiffindo:
                SpawnFieldSpellEffect(actor, FieldSpellDiffindo);
                break;
            case FieldSpellWingardiumLeviosa:
                SpawnFieldSpellEffect(actor, FieldSpellWingardiumLeviosa);
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

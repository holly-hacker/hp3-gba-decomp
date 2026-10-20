#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "sound.h"
#include "world_actors.h"

// Collision callback of the effect actor's second box: Flipendo bursts on a prop of kind 0x3A.
// The kind is read from the effect's own scriptState, where HandleFieldSpellHit reads the
// target's.
void HandleFieldSpellSecondaryHit(Actor *effect, Actor *target)
{
    u8 spell;

    if (target->wActorType != 0
        && (effect->wCharacterId_candidate == FieldSpellReparo || (target->dwFlags & ActorFlagVisible))
        && !(effect->dwFlags & ActorFlagNoPushTrigger_candidate)
        && !(target->dwFlags & ActorFlagNoPushTrigger_candidate))
    {
        spell = effect->wCharacterId_candidate;
        switch (effect->wCharacterId_candidate)
        {
        case FieldSpellFlipendo:
            if (target->wActorType == RoomActorType_ScriptedTrigger
                && ROOM_ACTOR_TRIGGER_STATE(effect)->bKind == 0x3A)
            {
                PlaySoundById(0x50);
                effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
                CancelActorMove_candidate(effect);
                SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                                 g_aaFieldSpellImpactAnims[g_abFacingDirection4[effect->pLinkedActor_candidate->bFacing]], 0);
                if (g_abFacingDirection4[effect->pLinkedActor_candidate->bFacing] == 3)
                    effect->oam.hFlip = 1;
                effect->dwStateTimer = 14;
            }
            break;
        }
    }
}

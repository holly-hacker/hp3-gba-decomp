#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "sound.h"
#include "world_actors.h"

// Collision callback of the effect actor's second box: Flipendo bursts on a world actor of kind 0x3A.
// The kind is read from the effect's own scriptState, where HandleFieldSpellHit reads the
// target's.
void HandleFieldSpellSecondaryHit(Actor *effect, Actor *target)
{
    u8 spell;

    if (target->wActorType != RoomActorType_Player
        && (effect->wSubtype == FieldSpellReparo || (target->dwFlags & ActorFlagVisible))
        && !(effect->dwFlags & ActorFlagSettled)
        && !(target->dwFlags & ActorFlagSettled))
    {
        spell = effect->wSubtype;
        switch (effect->wSubtype)
        {
        case FieldSpellFlipendo:
            if (target->wActorType == RoomActorType_WorldActor
                && WORLD_ACTOR_STATE(effect)->bKind == 0x3A)
            {
                PlaySoundById(0x50);
                effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
                StopActorMotion(effect);
                SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                                 g_aaFieldSpellImpactAnims[g_abFacingDirection4[effect->pLinkedActor->bFacing]], 0);
                if (g_abFacingDirection4[effect->pLinkedActor->bFacing] == 3)
                    effect->oam.hFlip = 1;
                effect->dwStateTimer = 14;
            }
            break;
        }
    }
}

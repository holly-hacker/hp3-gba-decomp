#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "sound.h"
#include "world_actors.h"

// Collision callback of the effect actor's first box: runs the field spell on the room actor
// it touches. Chests forward their own touches here too.
void HandleFieldSpellHit(Actor *effect, Actor *target)
{
    u8 spell;

    if (target->wActorType == RoomActorType_Player)
        return;
    if (effect->wSubtype != FieldSpellReparo && !(target->dwFlags & ActorFlagVisible))
        return;
    if (effect->dwFlags & ActorFlagSettled)
        return;
    if (target->dwFlags & ActorFlagSettled)
        return;
    if (target->wActorType == RoomActorType_Switch
        && (target->bKind <= 2 || target->bKind == 6))
        return;

    spell = effect->wSubtype;
    switch (effect->wSubtype)
    {
    case FieldSpellFlipendo:
        if (target->wActorType == RoomActorType_WorldActor)
        {
            if (WORLD_ACTOR_STATE(target)->bPushable != 0)
            {
                PlaySoundById(0x50);
                effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
                StopActorMotion(effect);
                SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                                 g_aaFieldSpellImpactAnims[g_abFacingDirection4[effect->pLinkedActor->bFacing]], 0);
                if (g_abFacingDirection4[effect->pLinkedActor->bFacing] == 3)
                    effect->oam.hFlip = 1;
                effect->dwStateTimer = 14;
                break;
            }
            if (WORLD_ACTOR_STATE(target)->bBrokenFrame != 0xFF)
                break;
        }
        PlaySoundById(0x50);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
        effect->dwStateTimer = 20;
        break;
    case FieldSpellReparo:
        if (target->wActorType == RoomActorType_TriggerZone && target->bKind != 3)
            break;
        PlaySoundById(0x20);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
        effect->dwStateTimer = 20;
        if (target->wActorType == RoomActorType_TriggerZone && target->bKind == 3
            && g_abFacingDirection4[effect->pLinkedActor->bFacing] == 3)
            effect->oam.hFlip = 1;
        if (WORLD_ACTOR_STATE(target)->bBrokenFrame != 0xFF && WORLD_ACTOR_STATE(target)->bBreakable != 0
            && effect->pLinkedActor == g_pPlayerActor)
        {
            StopActorMotion(effect->pLinkedActor);
            SetPartyMemberAnim(g_pPlayerActor, PartyAnimStand);
            SetActorActionState(effect->pLinkedActor, 0);
            SetActorPrevActionState(effect->pLinkedActor, 0x21);
        }
        break;
    case FieldSpellAlohomora:
        if (target->wActorType == RoomActorType_WorldActor && WORLD_ACTOR_STATE(target)->b66 != 0)
        {
            PlaySoundById(0x52);
            effect->dwStateTimer = 0x44;
            effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollision
                                 | ActorFlagTerrainDrawLayer);
            SetActorActionState(effect, 0);
            if (effect->pLinkedActor == g_pPlayerActor)
            {
                StopActorMotion(effect->pLinkedActor);
                SetPartyMemberAnim(g_pPlayerActor, PartyAnimStand);
                SetActorActionState(g_pPlayerActor, 0);
                SetActorPrevActionState(g_pPlayerActor, 0x21);
            }
            effect->pLinkedActor = target;
        }
        else if (target->dwFlags != 0)
        {
            PlaySoundById(0x52);
            effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
            StopActorMotion(effect);
            SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
            effect->dwStateTimer = 20;
        }
        break;
    case FieldSpellGlacius:
        if (effect->dwFlags & ActorFlagWantsCollisionCheck)
            PlaySoundById(0x50);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        if (target->wActorType == RoomActorType_WorldActor && WORLD_ACTOR_STATE(target)->bKind >= 0x33
            && WORLD_ACTOR_STATE(target)->bKind <= 0x34)
            SetActorActionSubState(effect, 0x10);
        else
            SetActorActionSubState(effect, 0x11);
        break;
    case FieldSpellSpongify:
        if (effect->dwFlags & ActorFlagWantsCollisionCheck)
            PlaySoundById(0x56);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        if (target->wActorType == RoomActorType_SpongifyPad)
        {
            SetActorActionSubState(effect, 0x10);
            SetActorPosition(effect, (s16)(target->pos.x >> 16), (s16)(target->pos.y >> 16) - 20);
        }
        else
            SetActorActionSubState(effect, 0x11);
        break;
    case FieldSpellDiffindo:
        if (effect->dwFlags & ActorFlagWantsCollisionCheck)
            PlaySoundById(0x54);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagSpellTerrainCollision);
        StopActorMotion(effect);
        if (target->wActorType == RoomActorType_WorldActor
            && ((WORLD_ACTOR_STATE(target)->bKind >= 0x2E && WORLD_ACTOR_STATE(target)->bKind <= 0x32)
                || WORLD_ACTOR_STATE(target)->bKind == 0x36 || WORLD_ACTOR_STATE(target)->bKind == 0x4D))
        {
            SetActorActionSubState(effect, 0x10);
            SetActorPosition(effect, (s16)(target->pos.x >> 16), (s16)(target->pos.y >> 16) - 15);
        }
        else
            SetActorActionSubState(effect, 0x11);
        break;
    case FieldSpellLumos:
    case FieldSpellWingardiumLeviosa:
        break;
    }
}

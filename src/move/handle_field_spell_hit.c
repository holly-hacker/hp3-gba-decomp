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

    if (target->wActorType == 0)
        return;
    if (effect->wCharacterId_candidate != FieldSpellReparo && !(target->dwFlags & ActorFlagVisible))
        return;
    if (effect->dwFlags & ActorFlagNoPushTrigger_candidate)
        return;
    if (target->dwFlags & ActorFlagNoPushTrigger_candidate)
        return;
    if (target->wActorType == 3
        && (target->bRoomActorKind_candidate <= 2 || target->bRoomActorKind_candidate == 6))
        return;

    spell = effect->wCharacterId_candidate;
    switch (effect->wCharacterId_candidate)
    {
    case FieldSpellFlipendo:
        if (target->wActorType == RoomActorType_ScriptedTrigger)
        {
            if (ROOM_ACTOR_TRIGGER_STATE(target)->b63 != 0)
            {
                PlaySoundById(0x50);
                effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
                CancelActorMove_candidate(effect);
                SetActorAnimData(effect, &g_aFieldSpellAssets[spell],
                                 g_aaFieldSpellImpactAnims[g_abFacingDirection4[effect->pLinkedActor_candidate->bFacing]], 0);
                if (g_abFacingDirection4[effect->pLinkedActor_candidate->bFacing] == 3)
                    effect->oam.hFlip = 1;
                effect->dwStateTimer = 14;
                break;
            }
            if (ROOM_ACTOR_TRIGGER_STATE(target)->b67 != 0xFF)
                break;
        }
        PlaySoundById(0x50);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
        CancelActorMove_candidate(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
        effect->dwStateTimer = 20;
        break;
    case FieldSpellReparo:
        if (target->wActorType == 4 && target->bRoomActorKind_candidate != 3)
            break;
        PlaySoundById(0x20);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
        CancelActorMove_candidate(effect);
        SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
        effect->dwStateTimer = 20;
        if (target->wActorType == 4 && target->bRoomActorKind_candidate == 3
            && g_abFacingDirection4[effect->pLinkedActor_candidate->bFacing] == 3)
            effect->oam.hFlip = 1;
        if (ROOM_ACTOR_TRIGGER_STATE(target)->b67 != 0xFF && ROOM_ACTOR_TRIGGER_STATE(target)->b64 != 0
            && effect->pLinkedActor_candidate == g_pPlayerActor)
        {
            CancelActorMove_candidate(effect->pLinkedActor_candidate);
            SetPartyMemberAnim(g_pPlayerActor, PartyAnimStand);
            SetActorActionState(effect->pLinkedActor_candidate, 0);
            SetActorPrevActionState(effect->pLinkedActor_candidate, 0x21);
        }
        break;
    case FieldSpellAlohomora:
        if (target->wActorType == RoomActorType_ScriptedTrigger && ROOM_ACTOR_TRIGGER_STATE(target)->b66 != 0)
        {
            PlaySoundById(0x52);
            effect->dwStateTimer = 0x44;
            effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate
                                 | ActorFlagTerrainDrawLayer);
            SetActorActionState(effect, 0);
            if (effect->pLinkedActor_candidate == g_pPlayerActor)
            {
                CancelActorMove_candidate(effect->pLinkedActor_candidate);
                SetPartyMemberAnim(g_pPlayerActor, PartyAnimStand);
                SetActorActionState(g_pPlayerActor, 0);
                SetActorPrevActionState(g_pPlayerActor, 0x21);
            }
            effect->pLinkedActor_candidate = target;
        }
        else if (target->dwFlags != 0)
        {
            PlaySoundById(0x52);
            effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
            CancelActorMove_candidate(effect);
            SetActorAnimData(effect, &g_aFieldSpellAssets[spell], g_aaFieldSpellAnims[spell], 0);
            effect->dwStateTimer = 20;
        }
        break;
    case FieldSpellGlacius:
        if (effect->dwFlags & ActorFlagWantsCollisionCheck)
            PlaySoundById(0x50);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
        CancelActorMove_candidate(effect);
        if (target->wActorType == RoomActorType_ScriptedTrigger && ROOM_ACTOR_TRIGGER_STATE(target)->bKind >= 0x33
            && ROOM_ACTOR_TRIGGER_STATE(target)->bKind <= 0x34)
            SetActorActionSubState(effect, 0x10);
        else
            SetActorActionSubState(effect, 0x11);
        break;
    case FieldSpellSpongify:
        if (effect->dwFlags & ActorFlagWantsCollisionCheck)
            PlaySoundById(0x56);
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
        if (target->wActorType == 10)
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
        effect->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionB_candidate);
        CancelActorMove_candidate(effect);
        if (target->wActorType == RoomActorType_ScriptedTrigger
            && ((ROOM_ACTOR_TRIGGER_STATE(target)->bKind >= 0x2E && ROOM_ACTOR_TRIGGER_STATE(target)->bKind <= 0x32)
                || ROOM_ACTOR_TRIGGER_STATE(target)->bKind == 0x36 || ROOM_ACTOR_TRIGGER_STATE(target)->bKind == 0x4D))
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

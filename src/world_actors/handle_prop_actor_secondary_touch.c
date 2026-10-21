#include "types.h"
#include "actor.h"
#include "hero.h"
#include "input.h"
#include "sound.h"
#include "world_actors.h"

// Collision box 1: the player presses A at kind 44, Flipendo triggers kind 58. Actors
// crossing a block sunk in water skip their next terrain pass.
void HandlePropActorSecondaryTouch(Actor *pSelf, Actor *pOther)
{
    u8 kind = ROOM_ACTOR_TRIGGER_STATE(pSelf)->bKind;

    switch (pOther->wActorType)
    {
    case RoomActorType_Player:
        if (pOther->bActionState != 0x24 && kind == 44 && ROOM_ACTOR_TRIGGER_STATE(pSelf)->bActivated == 0
            && (g_wKeysPressed & KeyA))
        {
            ROOM_ACTOR_TRIGGER_STATE(pSelf)->bActivated = 1;
            SetActorActionState(pSelf, 4);
            PlaySoundById(0x1D);
        }
        break;
    case RoomActorType_FieldSpellEffect:
        if (pOther->wCharacterId_candidate == FieldSpellFlipendo && kind == 58)
        {
            SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
            SetActorActionState(pSelf, 0);
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        }
        break;
    }

    if ((pSelf->dwFlags & ActorFlagNoPushTrigger_candidate)
        && (pOther->wActorType == RoomActorType_ScriptedTrigger || pOther->wActorType == RoomActorType_Player))
        pOther->dwFlags |= ActorFlagSkipTerrainOnce_candidate;
}

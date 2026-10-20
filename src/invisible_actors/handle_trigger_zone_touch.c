#include "types.h"
#include "area.h"
#include "input.h"
#include "move.h"
#include "hero.h"
#include "overworld/room_actor.h"
#include "invisible_actors.h"

// Collision callback of a trigger zone's first box. Kinds 3-5 fire when hit
// by the Reparo, Alohomora or Glacius field spell effect; the others when
// the player touches the zone, with A if the record requires it.
void HandleTriggerZoneTouch(Actor *pSelf, Actor *pOther)
{
    u32 kind = pSelf->bRoomActorKind_candidate;

    if (kind == 3)
    {
        if (pOther->wActorType == 0xF && pOther->wCharacterId_candidate == FieldSpellReparo)
        {
            SetActorActionState(pSelf, 5);
            HandleFieldSpellHit(pOther, pSelf);
        }
    }
    else if (kind == 4)
    {
        if (pOther->wActorType == 0xF && pOther->wCharacterId_candidate == FieldSpellAlohomora)
            SetActorActionState(pSelf, 5);
    }
    else if (kind == 5)
    {
        if (pOther->wActorType == 0xF && pOther->wCharacterId_candidate == FieldSpellGlacius)
        {
            SetActorActionState(pSelf, 5);
            SetActorActionSubState(pOther, 0x10);
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        }
    }
    else if (pOther->wActorType == RoomActorType_Player && pOther->bActionState == 0x21)
    {
        if (ROOM_ACTOR_WORD_STATE(pSelf)->b70 == 0 || (g_wKeysPressed & KeyA))
        {
            // Kind 0 fires once; the others re-arm.
            if (kind == 0)
                SetActorActionState(pSelf, 5);
            else
                SetActorActionState(pSelf, 4);
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        }
    }
}

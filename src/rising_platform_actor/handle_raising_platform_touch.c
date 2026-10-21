#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "move.h"
#include "rising_platform_actor.h"

// Collision callback: the player starts the party gathering on an active platform,
// and a Reparo spell effect activates an inactive one.
void HandleRaisingPlatformTouch(Actor *pSelf, Actor *pOther)
{
    switch (pOther->wActorType)
    {
    case RoomActorType_Player:
        if (RAISING_PLATFORM_STATE(pSelf)->dwInactive == 0 && pSelf->bActionSubState == 10)
        {
            pOther->moveTarget.x = pSelf->pos.x;
            pOther->moveTarget.y = pSelf->pos.y;
            SetActorActionState(pOther, 0);
            SetActorActionSubState(pOther, 3);

            if (g_pFollowerActor0 != NULL)
            {
                g_pFollowerActor0->moveTarget.x = pSelf->pos.x;
                g_pFollowerActor0->moveTarget.y = pSelf->pos.y;
                SetActorActionSubState(g_pFollowerActor0, 3);
            }
            else
            {
                g_adwRoomActorUnkACState[1] = 1;
            }

            if (g_pFollowerActor1 != NULL)
            {
                g_pFollowerActor1->moveTarget.x = pSelf->pos.x;
                g_pFollowerActor1->moveTarget.y = pSelf->pos.y;
                SetActorActionSubState(g_pFollowerActor1, 3);
            }
            else
            {
                g_adwRoomActorUnkACState[2] = 1;
            }

            SetActorActionSubState(pSelf, 19);
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        }
        break;
    case RoomActorType_FieldSpellEffect:
        if (pOther->wCharacterId_candidate == FieldSpellReparo && RAISING_PLATFORM_STATE(pSelf)->dwInactive == 1)
        {
            RAISING_PLATFORM_STATE(pSelf)->dwInactive = 0;
            HandleFieldSpellHit(pOther, pSelf);
            SetActorAnimData(pSelf, &g_RoomRaisingPlatformSprite, g_abRoomRaisingPlatformAnimData, 2);
            SetActorActionSubState(pSelf, 10);
        }
        break;
    }
}

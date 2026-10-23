#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "rising_platform_actor.h"

// Sub-states: 19 waits for the party to walk onto the platform (one
// g_adwPartyMemberArrived flag per member), 3 rises carrying the player, 2 walks
// the player off to the left, 20 lowers and releases the party, 5 destroys it.
void TickRaisingPlatformActor(Actor *pActor)
{
    u32 i;
    IntPoint anchor;
    u32 direction;
    FixedPoint pos;
    FixedPoint target;

    switch (pActor->bActionSubState)
    {
    case 19:
        if (g_adwPartyMemberArrived[0] == 0)
            g_adwPartyMemberArrived[0] = FaceActorTowardMoveTarget(g_pPlayerActor);
        if (g_pFollowerActor0 != NULL && g_adwPartyMemberArrived[1] == 0)
            g_adwPartyMemberArrived[1] = FaceActorTowardMoveTarget(g_pFollowerActor0);
        if (g_pFollowerActor1 != NULL && g_adwPartyMemberArrived[2] == 0)
            g_adwPartyMemberArrived[2] = FaceActorTowardMoveTarget(g_pFollowerActor1);

        if (g_adwPartyMemberArrived[0] != 0 && g_adwPartyMemberArrived[1] != 0
            && g_adwPartyMemberArrived[2] != 0)
        {
            if (g_pFollowerActor0 != NULL)
                g_pFollowerActor0->pOwnerActor = g_pPlayerActor;
            if (g_pFollowerActor1 != NULL)
                g_pFollowerActor1->pOwnerActor = g_pPlayerActor;
            StopActorMotion(g_pPlayerActor);
            SetActorActionSubState(g_pPlayerActor, 2);
            g_pPlayerActor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagHasAnimation
                                         | ActorFlagTerrainCollision);
            SetActorActionSubState(pActor, 3);
            SetActorAnimData(pActor, &g_RoomRaisingPlatformSprite, g_abRoomRaisingPlatformAnimData, 4);
        }
        break;
    case 3:
        if (pActor->dwFlags & ActorFlagActionAnimDone)
        {
            SetActorActionSubState(pActor, 2);
            g_pPlayerActor->moveTarget.x = g_pPlayerActor->pos.x - (25 << 16);
            g_pPlayerActor->moveTarget.y = g_pPlayerActor->pos.y;
            SetActorActionState(g_pPlayerActor, 0);
            SetActorActionSubState(g_pPlayerActor, 3);
            g_pPlayerActor->dwFlags |= ActorFlagHasAnimation;
        }
        else
        {
            StopActorMotion(g_pPlayerActor);
            g_pPlayerActor->dwFlags &= ~ActorFlagHasAnimation;
            GetActorAnchor(pActor, 0, &anchor);
            SnapActorPosition(g_pPlayerActor, pActor->pos.x + (anchor.x << 16),
                              pActor->pos.y + (anchor.y << 16));
        }
        break;
    case 2:
        pos = g_pPlayerActor->pos;
        target = g_pPlayerActor->moveTarget;
        direction = GetDirectionToTarget(g_pPlayerActor->dwFlags, pos, target, g_pPlayerActor->nMoveSpeed);
        if (direction == DirectionNone)
        {
            StopActorMotion(g_pPlayerActor);
            SetActorActionSubState(g_pPlayerActor, 2);
            SetActorActionSubState(pActor, 20);
            SetActorAnimData(pActor, &g_RoomRaisingPlatformSprite, g_abRoomRaisingPlatformAnimData, 14);
        }
        else if (g_pPlayerActor->bFacing != direction)
        {
            g_pPlayerActor->bFacing = direction;
            g_pPlayerActor->bActionFlags |= 0x10;
        }
        break;
    case 20:
        if (pActor->dwFlags & ActorFlagActionAnimDone)
        {
            if (g_pFollowerActor0 != NULL)
            {
                g_pFollowerActor0->dwFlags |= ActorFlagVisible;
                SetActorActionSubState(g_pFollowerActor0, 0);
                g_pFollowerActor0->pOwnerActor = NULL;
            }
            if (g_pFollowerActor1 != NULL)
            {
                g_pFollowerActor1->dwFlags |= ActorFlagVisible;
                SetActorActionSubState(g_pFollowerActor1, 0);
                g_pFollowerActor1->pOwnerActor = NULL;
            }
            g_pPlayerActor->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagTerrainCollision;
            StopActorMotion(g_pPlayerActor);
            SetActorActionSubState(g_pPlayerActor, 6);
            SetActorActionState(g_pPlayerActor, 0x21);
            pActor->dwFlags |= ActorFlagWantsCollisionCheck;
            SetActorActionSubState(pActor, 10);

            for (i = 0; i < ARRAY_COUNT(g_adwPartyMemberArrived); i++)
                g_adwPartyMemberArrived[i] = 0;

            if (RAISING_PLATFORM_STATE(pActor)->finish.wPair != 0)
                RespawnGroupAndRunChain(RAISING_PLATFORM_STATE(pActor)->finish.rows.bRespawnRow,
                                        RAISING_PLATFORM_STATE(pActor)->finish.rows.bChainRow);
        }
        break;
    case 5:
        if (pActor->pLinkedActor != NULL)
            pActor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 1:
        break;
    }
}

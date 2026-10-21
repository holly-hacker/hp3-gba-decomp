#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "math.h"
#include "move.h"
#include "spongify_pad_actor.h"

// Sub-states: 8 keeps the pad armed for 150 ticks, 19 waits for the party to gather
// on it and launches the player, 11 resets the pad, 5 destroys it.
void TickSpongifyPadActor(Actor *pActor)
{
    u32 i;

    switch (pActor->bActionSubState)
    {
    case 5:
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 8:
        if (pActor->dwStateTimer++ < 150)
        {
            g_dwFieldSpellActive = 1;
        }
        else
        {
            SPONGIFY_PAD_STATE(pActor)->dwArmed = 0;
            pActor->dwFlags &= ~ActorFlagHasAnimation;
            g_dwFieldSpellActive = 0;
            SetActorActionSubState(pActor, 1);
        }
        break;
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
            SetActorActionSubState(pActor, 11);
            pActor->dwStateTimer = 30;
            IntToFixedPoint(SPONGIFY_PAD_STATE(g_pPlayerActor)->target = SPONGIFY_PAD_STATE(pActor)->target,
                            &g_pPlayerActor->moveTarget);
            g_pPlayerActor->padFinish.rows.bRespawnRow = SPONGIFY_PAD_STATE(pActor)->bRespawnRow;
            g_pPlayerActor->padFinish.rows.bChainRow = SPONGIFY_PAD_STATE(pActor)->bChainRow;
            SpawnSpongifyPadEffect(pActor, g_pPlayerActor);
            ClearActorFlags(g_pPlayerActor, ActorFlagTerrainDrawLayer);
            SetActorDrawLayer(g_pPlayerActor, 0);
            SetActorDepthSortBias(g_pPlayerActor, 0);
            if (g_pFollowerActor0 != NULL)
            {
                ClearActorFlags(g_pFollowerActor0, ActorFlagTerrainDrawLayer);
                SetActorDrawLayer(g_pFollowerActor0, 0);
                SetActorDepthSortBias(g_pFollowerActor0, 0);
            }
            if (g_pFollowerActor1 != NULL)
            {
                ClearActorFlags(g_pFollowerActor1, ActorFlagTerrainDrawLayer);
                SetActorDrawLayer(g_pFollowerActor1, 0);
                SetActorDepthSortBias(g_pFollowerActor1, 0);
            }
            // Both arms are the same, so only a dead load of the variant survives; the
            // compared value is unknown.
            if (pActor->wCharacterId_candidate == 2)
            {
                SetActorActionState(g_pPlayerActor, 0x10);
                SetActorActionSubState(g_pPlayerActor, 0);
            }
            else
            {
                SetActorActionState(g_pPlayerActor, 0x10);
                SetActorActionSubState(g_pPlayerActor, 0);
            }
        }
        break;
    case 11:
        if (--pActor->dwStateTimer == -1)
        {
            pActor->dwFlags &= ~ActorFlagHasAnimation;
            SetActorActionSubState(pActor, 1);
            for (i = 0; i < ARRAY_COUNT(g_adwPartyMemberArrived); i++)
                g_adwPartyMemberArrived[i] = 0;
        }
        break;
    case 1:
        break;
    }
}

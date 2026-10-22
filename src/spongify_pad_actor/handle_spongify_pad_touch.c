#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "move.h"
#include "particles.h"
#include "spongify_pad_actor.h"

// Collision callback: a Spongify spell effect arms the pad, and the player stepping on
// an armed pad gathers the party on it. A moving RoomActorType_WorldActor is pushed back
// out unless its bFighterIndex is 4.
void HandleSpongifyPadTouch(Actor *pSelf, Actor *pOther)
{
    switch (pOther->wActorType)
    {
    case RoomActorType_Player:
        if (SPONGIFY_PAD_STATE(pSelf)->dwArmed == 1)
        {
            SPONGIFY_PAD_STATE(pSelf)->dwArmed = 0;
            pOther->moveTarget.x = pSelf->pos.x;
            pOther->moveTarget.y = pSelf->pos.y;
            SetActorActionState(pOther, 0);
            SetActorActionSubState(pOther, 3);
            ClearActorFlags(g_pPlayerActor, ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate);

            if (g_pFollowerActor0 != NULL)
            {
                g_pFollowerActor0->bFacing = DirectionUp;
                g_pFollowerActor0->moveTarget.x = pSelf->pos.x;
                g_pFollowerActor0->moveTarget.y = pSelf->pos.y;
                SetActorActionSubState(g_pFollowerActor0, 3);
                ClearActorFlags(g_pFollowerActor0, ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate);
            }
            else
            {
                g_adwPartyMemberArrived[1] = 1;
            }

            if (g_pFollowerActor1 != NULL)
            {
                g_pFollowerActor1->bFacing = DirectionUp;
                g_pFollowerActor1->moveTarget.x = pSelf->pos.x;
                g_pFollowerActor1->moveTarget.y = pSelf->pos.y;
                SetActorActionSubState(g_pFollowerActor1, 3);
                ClearActorFlags(g_pFollowerActor1, ActorFlagWantsCollisionCheck | ActorFlagTerrainCollisionA_candidate);
            }
            else
            {
                g_adwPartyMemberArrived[2] = 1;
            }

            SetActorActionSubState(pSelf, 19);
        }
        break;
    case RoomActorType_WorldActor:
        if (pOther->bFighterIndex != 4)
        {
            if (pOther->vel.x != 0)
                pOther->posPrev.x -= pOther->vel.x;
            if (pOther->vel.y != 0)
                pOther->posPrev.y -= pOther->vel.y;
            pSelf->vel.x = 0;
            pSelf->vel.y = 0;
            pOther->vel.x = 0;
            pOther->vel.y = 0;
        }
        break;
    case RoomActorType_FieldSpellEffect:
        if (pOther->wCharacterId_candidate == FieldSpellSpongify && SPONGIFY_PAD_STATE(pSelf)->dwArmed == 0)
        {
            ReleaseParticleGfx(2, 0);
            ReleaseParticleGfx(2, 1);
            FreeAllParticleEmitters();
            FreeAllParticles();
            SPONGIFY_PAD_STATE(pSelf)->dwArmed = 1;
            pSelf->dwFlags |= ActorFlagHasAnimation;
            SetActorActionSubState(pSelf, 8);
            g_dwFieldSpellActive = 1;
            pSelf->dwStateTimer = 0;
        }
        break;
    }
}

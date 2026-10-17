#include "types.h"
#include "actor.h"
#include "actor_inline.h"
#include "area.h"
#include "overworld/room_actor.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "overworld/room_script_bytecode.h"
#include "hero.h"

// Action state 0x11: walks the party leader to the pixel position in Actor bytes
// 0x60/0x64 with its followers hidden, faces bPadFinalFacing, then hands control back
// (action state 0x21).
void TickActorPadWalk(Actor *actor)
{
    u8 subState;
    u8 direction;

    subState = actor->bActionSubState;
    switch (subState) {
    case 0:
        actor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollisionA_candidate);
        if (g_pFollowerActor0 != 0) {
            g_pFollowerActor0->dwFlags &= ~ActorFlagVisible;
            g_pFollowerActor0->bFacing = actor->bFacing;
        }
        if (g_pFollowerActor1 != 0) {
            g_pFollowerActor1->dwFlags &= ~ActorFlagVisible;
            g_pFollowerActor1->bFacing = actor->bFacing;
        }
        SetActorActionSubState(actor, 3);
        actor->moveTarget.x = ROOM_ACTOR_WORD_STATE(actor)->n60 << 16;
        actor->moveTarget.y = ROOM_ACTOR_WORD_STATE(actor)->n64 << 16;
        break;
    case 3:
        actor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollisionA_candidate);
        direction = GetDirectionToTarget(actor->dwFlags, actor->pos, actor->moveTarget, actor->nMoveSpeed);
        if (((actor->dwFlags & ActorFlagFourWayDirections_candidate) && direction == Direction4None)
            || direction == DirectionNone) {
            direction = actor->bPadFinalFacing;
            if (actor->bFacing != direction) {
                actor->bFacing = direction;
                actor->bActionFlags |= 0x10;
            }
            CancelActorMove_candidate(actor);
            SetActorActionSubState(actor, 14);
        }
        else if (actor->bFacing != direction) {
            actor->bFacing = direction;
            actor->bActionFlags |= 0x10;
        }
        break;
    case 14:
        actor->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollisionA_candidate;
        if (g_pFollowerActor0 != 0) {
            g_pFollowerActor0->dwFlags |= ActorFlagVisible;
            SetActorActionSubState(g_pFollowerActor0, 0);
            g_pFollowerActor0->pOwnerActor = 0;
        }
        if (g_pFollowerActor1 != 0) {
            g_pFollowerActor1->dwFlags |= ActorFlagVisible;
            SetActorActionSubState(g_pFollowerActor1, 0);
            g_pFollowerActor1->pOwnerActor = 0;
        }
        g_pPlayerShadowActor_candidate->dwFlags |= ActorFlagVisible;
        actor->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollisionA_candidate;
        SetActorActionState(actor, 0x21);
        if (actor->padFinish.wPair != 0)
            RespawnGroupAndRunChain(actor->padFinish.rows.bRespawnRow,
                                            actor->padFinish.rows.bChainRow);
        if ((actor->dwFlags & ActorFlagRoomScriptYield) && g_bRoomScriptYieldOpcode == RSOP_StartTileActorScript) {
            actor->dwFlags &= ~ActorFlagRoomScriptYield;
            ResumeRoomScriptChain();
        }
        break;
    default:
        TickActorIdle(actor);
        break;
    }
}

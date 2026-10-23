#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "particles.h"
#include "world_actors.h"

// pfnTick of a world actor. A pushable one slows by half a pixel per tick; sub-states 12-13 sink a
// block pushed onto water (see SnapActorXToTileGrid). Action state 4 runs the kind's
// activation, 2 waits out a break or Reparo restore, 33 lets the player steer it.
void TickWorldActor(Actor *pActor)
{
    u8 kind = WORLD_ACTOR_STATE(pActor)->bKind;

    if (WORLD_ACTOR_STATE(pActor)->bPushable != 0)
    {
        if (pActor->vel.x < 0)
            pActor->vel.x += 0x8000;
        else if (pActor->vel.x > 0)
            pActor->vel.x -= 0x8000;
        else if (pActor->vel.y < 0)
            pActor->vel.y += 0x8000;
        else if (pActor->vel.y > 0)
            pActor->vel.y -= 0x8000;
    }

    switch (pActor->bActionSubState)
    {
    case 6:
        if (WORLD_ACTOR_STATE(pActor)->bPushable != 0)
        {
            WORLD_ACTOR_STATE(pActor)->bPushable = 0;
            SetActorActionState(pActor, 0);
        }
        break;
    case 3:
        pActor->nMoveSpeed = 0x20000;
        break;
    case 2:
        pActor->vel.x = 0;
        pActor->vel.y = 0;
        SetActorActionSubState(pActor, 1);
        break;
    case 11:
        if (kind == 39)
        {
            SetActorActionSubState(pActor, 1);
            SetActorActionState(pActor, 0);
            SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 3);
        }
        else if (kind == 90)
        {
            SetActorActionSubState(pActor, 1);
            SetActorActionState(pActor, 0);
            SetActorAnimFrame(pActor, 1);
        }
        else
        {
            SetActorActionSubState(pActor, 1);
            SetActorActionState(pActor, 4);
            SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
        }
        break;
    case 12:
        if (--pActor->dwStateTimer == (u32)-1)
        {
            SetActorActionSubState(pActor, 13);
            pActor->dwStateTimer = 12;
            pActor->accel.y = 0x8000;
            pActor->vel.y = 0x14000;
        }
        break;
    case 13:
        if (--pActor->dwStateTimer == (u32)-1)
        {
            pActor->accel.y = 0;
            pActor->vel.x = 0;
            pActor->vel.y = 0;
            SetActorActionSubState(pActor, 1);
            SetActorAnimFrame(pActor, 1);
            pActor->dwFlags |= ActorFlagSettled;
            pActor->bDepthSortBias = 0xFF;
        }
        break;
    case 5:
        if (pActor->pLinkedActor != NULL)
            pActor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        return;
    }

    switch (pActor->bActionState)
    {
    case 0:
        break;
    case 33:
        TickWorldActorPlayerControl(pActor);
        break;
    case 2:
        if (kind == 46 || kind == 47 || kind == 48 || kind == 49 || kind == 50 || kind == 54 || kind == 77)
        {
            if (pActor->dwFlags & ActorFlagActionAnimDone)
            {
                if (WORLD_ACTOR_STATE(pActor)->bChainRow != 0)
                    RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
                SetActorActionState(pActor, 1);
            }
        }
        else if (--pActor->dwStateTimer == 0)
        {
            if (WORLD_ACTOR_STATE(pActor)->bBrokenFrame != 0xFF
                && WORLD_ACTOR_STATE(pActor)->bBrokenFrame >= 80)
            {
                SetActorAnimFrame(pActor, WORLD_ACTOR_STATE(pActor)->bBrokenFrame - 80);
                WORLD_ACTOR_STATE(pActor)->bBrokenFrame = 0xFF;
            }
            SetActorActionState(pActor, 0);
            FreeAllParticleEmitters();
            FreeAllParticles();
            ReleaseParticleGfx(1, 0);
            ReleaseParticleGfx(1, 1);
            ReleaseParticleGfx(1, 2);
        }
        break;
    case 5:
        if (kind == 1 || kind == 81)
        {
            SetActorActionSubState(pActor, 6);
            SetActorActionState(pActor, 0);
            WORLD_ACTOR_STATE(pActor)->bPushable = 0;
            pActor->vel.x = 0;
            pActor->vel.y = 0;
            if (kind == 81)
                SetActorAnimFrame(pActor, 1);
            else
                SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
            RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
        }
        else
        {
            SetActorActionSubState(pActor, 1);
            SetActorActionState(pActor, 4);
            SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
        }
        break;
    case 4:
        if (kind == 26 || kind == 27 || kind == 28 || kind == 29 || kind == 30
            || kind == 31 || kind == 32 || kind == 33 || kind == 34 || kind == 35
            || kind == 36 || kind == 37 || kind == 38 || kind == 39 || kind == 40
            || kind == 41 || kind == 42 || kind == 43 || kind == 44 || kind == 45)
        {
            SetActorActionSubState(pActor, 1);
            SetActorActionState(pActor, 0);
            if (WORLD_ACTOR_STATE(pActor)->b60 & 1)
            {
                SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 0);
                WORLD_ACTOR_STATE(pActor)->b60 &= ~1;
            }
            else
            {
                if (kind == 39)
                    SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 3);
                else
                    SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
                WORLD_ACTOR_STATE(pActor)->b60 |= 1;
            }
            RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
        }
        else if (kind == 90)
        {
            SetActorActionSubState(pActor, 1);
            SetActorActionState(pActor, 0);
            SetActorAnimFrame(pActor, 1);
        }
        else if (kind == 80)
        {
            if (pActor->dwFlags & ActorFlagActionAnimDone)
            {
                SetActorAnimData(pActor, g_apWorldActorAnimFrames[kind], g_abWorldActorAnimData[kind], 2);
                WORLD_ACTOR_STATE(pActor)->bActivated = 1;
                if (WORLD_ACTOR_STATE(pActor)->bChainRow != 0)
                    RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
            }
        }
        else if (kind == 68)
        {
            WORLD_ACTOR_STATE(pActor)->bActivated = 1;
            if (WORLD_ACTOR_STATE(pActor)->bChainRow != 0)
                RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
        }
        else if (kind == 62)
        {
            pActor->dwFlags &= ~(ActorFlagVisible | ActorFlagWantsCollisionCheck);
            WORLD_ACTOR_STATE(pActor)->bActivated = 1;
            if (WORLD_ACTOR_STATE(pActor)->bChainRow != 0)
                RespawnGroupAndRunChain(0, WORLD_ACTOR_STATE(pActor)->bChainRow);
        }
        else if (kind == 6)
        {
            if (pActor->dwStateTimer != 0)
            {
                pActor->dwStateTimer--;
            }
            else
            {
                SetActorActionState(g_pPlayerActor, 0x21);
                SetActorPrevActionState(g_pPlayerActor, 0x21);
                if (pActor->pLinkedActor != NULL)
                    pActor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
                pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            }
        }
        else if (pActor->dwFlags & ActorFlagActionAnimDone)
        {
            if (pActor->pLinkedActor != NULL)
                pActor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
            pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        }
        else if (kind == 51)
        {
            MarkRoomActorConsumed(pActor);
        }
        break;
    case 1:
        if (pActor->pLinkedActor != NULL)
            pActor->pLinkedActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    }
}

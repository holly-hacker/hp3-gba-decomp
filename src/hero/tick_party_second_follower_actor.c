#include "types.h"
#include "actor.h"
#include "hero.h"
#include "hero_inline.h"
#include "math.h"
#include "mem.h"
#include "overworld/overworld.h"

// pfnTick of follower 1. Records the player's steps into the trail and moves both
// followers along it, in place of TickPartyFollowerActor.
void TickPartySecondFollowerActor(Actor *actor)
{
    Actor *player;
    FixedPoint delta;
    u8 facing;

    switch (actor->bActionSubState)
    {
    case 0:
        SnapActorPosition(actor, g_pPlayerActor->pos.x, g_pPlayerActor->pos.y);
        SetActorActionSubState(actor, 9);
        actor->vel.x = 0;
        actor->vel.y = 0;
        memset(g_pPartyTrail, 0, PARTY_TRAIL_LENGTH * sizeof(PartyTrailStep));
        g_PartyTrailLastPos = g_pPlayerActor->pos;
        break;
    case 5:
        DestroyPartyMemberActor(actor);
        break;
    case 3:
        if (actor->bActionFlags & 0x12)
        {
            actor->bActionFlags = 0;
            actor->vel.x = FixedMultiply(g_aDirection8Vectors[actor->bFacing][0], actor->nMoveSpeed);
            actor->vel.y = FixedMultiply(g_aDirection8Vectors[actor->bFacing][1], actor->nMoveSpeed);
            SetPartyMemberAnim(actor, PartyAnimWalk);
        }
        break;
    case 2:
        if (actor->bActionFlags & 2)
        {
            actor->bActionFlags = 0;
            CancelActorMove_candidate(actor);
            SetPartyMemberAnim(actor, PartyAnimStand);
        }
        break;
    case 9:
        player = g_pPlayerActor;
        delta.x = player->pos.x - g_PartyTrailLastPos.x;
        delta.y = player->pos.y - g_PartyTrailLastPos.y;
        if (delta.x != 0 || delta.y != 0)
        {
            g_pPartyTrail[g_bPartyTrailWriteIndex].delta = delta;
            g_pPartyTrail[g_bPartyTrailWriteIndex].wFacing = player->bFacing;
            g_pPartyTrail[g_bPartyTrailWriteIndex].wAnimPaused = (player->dwFlags >> 28) & 1;
            if (++g_bPartyTrailWriteIndex == PARTY_TRAIL_LENGTH)
                g_bPartyTrailWriteIndex = 0;
            g_PartyTrailLastPos = player->pos;
        }

        if (delta.x != 0 || delta.y != 0)
        {
            // Forces the walk animation to restart when a follower starts moving.
            if (g_pFollowerActor0->vel.x == 0 && g_pFollowerActor0->vel.y == 0)
                g_pFollowerActor0->bFacing = 0x2A;
            g_pFollowerActor0->vel = g_pPartyTrail[g_bPartyTrailReadIndex0].delta;
            g_pFollowerActor0->dwFlags &= ~ActorFlagAnimPaused;
            if (g_pPartyTrail[g_bPartyTrailReadIndex0].wAnimPaused)
                g_pFollowerActor0->dwFlags |= ActorFlagAnimPaused;
            if (++g_bPartyTrailReadIndex0 == PARTY_TRAIL_LENGTH)
                g_bPartyTrailReadIndex0 = 0;
            // BUG: should take the facing of the step just replayed, as follower 1 does.
            facing = g_pPartyTrail[g_bPartyTrailReadIndex0].wFacing;
            if (g_pFollowerActor0->bFacing != facing)
            {
                g_pFollowerActor0->bFacing = facing;
                SetPartyMemberAnim(g_pFollowerActor0, PartyAnimWalk);
            }

            if (g_pFollowerActor1->vel.x == 0 && g_pFollowerActor1->vel.y == 0)
                g_pFollowerActor1->bFacing = 0x2A;
            g_pFollowerActor1->vel = g_pPartyTrail[g_bPartyTrailReadIndex1].delta;
            facing = g_pPartyTrail[g_bPartyTrailReadIndex1].wFacing;
            g_pFollowerActor1->dwFlags &= ~ActorFlagAnimPaused;
            if (g_pPartyTrail[g_bPartyTrailReadIndex1].wAnimPaused)
                g_pFollowerActor1->dwFlags |= ActorFlagAnimPaused;
            if (++g_bPartyTrailReadIndex1 == PARTY_TRAIL_LENGTH)
                g_bPartyTrailReadIndex1 = 0;
            if (g_pFollowerActor1->bFacing != facing)
            {
                g_pFollowerActor1->bFacing = facing;
                SetPartyMemberAnim(g_pFollowerActor1, PartyAnimWalk);
            }
        }
        else
        {
            CancelActorMove_candidate(actor);
            SetPartyMemberAnim(actor, PartyAnimStand);
            CancelActorMove_candidate(g_pFollowerActor0);
            SetPartyMemberAnim(g_pFollowerActor0, PartyAnimStand);
        }
        break;
    }
}

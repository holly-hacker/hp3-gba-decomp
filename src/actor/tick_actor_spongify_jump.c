#include "types.h"
#include "area.h"
#include "math.h"
#include "hw/bios.h"
#include "actor.h"
#include "sound.h"
#include "overworld/room_script_bytecode.h"
#include "hero.h"
#include "map.h"

// Action state 0x10: a Spongify pad bounces the party leader along a parabola from its
// position to moveTarget, its followers hidden, then hands control back (action state 0x21).
void TickActorSpongifyJump(Actor *actor)
{
    u8 subState;
    IntPoint pos;
    IntPoint target;
    s32 curve;
    s32 apexX;
    u16 apexY;
    s32 height;
    s32 step;

    subState = actor->bActionSubState;
    FixedToIntPoint(actor->pos, &pos);
    FixedToIntPoint(actor->moveTarget, &target);
    curve = actor->modeState.arc.nCurve;
    apexX = actor->modeState.arc.wApexX;
    apexY = actor->wArcApexY;

    switch (subState) {
    case 0:
        g_dwPauseMenuLocked = 1;
        SetActorActionSubState(actor, 15);
        StopActorMotion(actor);
        actor->dwFlags &= ~(ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollision);
        apexX = actor->modeState.arc.wApexX = (target.x + pos.x) / 2;
        if (pos.x < target.x) {
            actor->bFacing = DirectionRight;
            actor->dwArcRightward = 1;
        }
        else {
            actor->bFacing = DirectionLeft;
            actor->dwArcRightward = 0;
        }

        if (g_pFollowerActor0 != 0) {
            g_pFollowerActor0->dwFlags &= ~ActorFlagVisible;
            g_pFollowerActor0->bFacing = actor->bFacing;
            g_pFollowerActor0->pShadowActor->dwFlags &= ~ActorFlagVisible;
        }
        if (g_pFollowerActor1 != 0) {
            g_pFollowerActor1->dwFlags &= ~ActorFlagVisible;
            g_pFollowerActor1->bFacing = actor->bFacing;
            g_pFollowerActor1->pShadowActor->dwFlags &= ~ActorFlagVisible;
        }
        actor->pShadowActor->dwFlags &= ~ActorFlagVisible;

        if (apexX <= 399)
            height = 55;
        else if (apexX <= 509)
            height = 35;
        else
            height = 40;

        if (pos.y < target.y)
            apexY = actor->wArcApexY = pos.y - height;
        else
            apexY = actor->wArcApexY = target.y - height;

        curve = actor->modeState.arc.nCurve
            = (pos.y - apexY) * 100000 / ((pos.x - apexX) * (pos.x - apexX));
        if (actor->dwArcRightward)
            actor->wArcEndX = bios_Sqrt((target.y - apexY) * 100000 / curve) + apexX;
        else
            actor->wArcEndX = apexX - bios_Sqrt((target.y - apexY) * 100000 / curve);
        PlaySoundById(9);
        break;
    case 15:
        if (apexX <= 509)
            step = 2;
        else if (apexX <= 634)
            step = 1;
        else
            step = 3;

        if (actor->dwArcRightward) {
            pos.x += step;
            if (pos.x > actor->wArcEndX) {
                SetActorActionSubState(actor, 2);
                break;
            }
        }
        else {
            pos.x -= step;
            if (pos.x < actor->wArcEndX) {
                SetActorActionSubState(actor, 14);
                break;
            }
        }
        pos.y = curve * (pos.x - apexX) * (pos.x - apexX) / 100000 + apexY;
        IntToFixedPoint(pos, &actor->pos);
        break;
    case 2:
        SetActorActionSubState(actor, 14);
        break;
    case 14:
        actor->dwFlags |= ActorFlagWantsCollisionCheck | ActorFlagHasAnimation | ActorFlagTerrainCollision;
        actor->pShadowActor->dwFlags |= ActorFlagVisible;
        SetPartyMemberAnim(actor, PartyAnimStand);
        if (g_pFollowerActor0 != 0) {
            g_pFollowerActor0->dwFlags |= ActorFlagVisible;
            g_pFollowerActor0->pShadowActor->dwFlags |= ActorFlagVisible;
            SetActorActionSubState(g_pFollowerActor0, 0);
            g_pFollowerActor0->pOwnerActor = 0;
        }
        if (g_pFollowerActor1 != 0) {
            g_pFollowerActor1->dwFlags |= ActorFlagVisible;
            g_pFollowerActor1->pShadowActor->dwFlags |= ActorFlagVisible;
            SetActorActionSubState(g_pFollowerActor1, 0);
            g_pFollowerActor1->pOwnerActor = 0;
        }

        if (actor->padFinish.wPair != 0) {
            RespawnGroupAndRunChain(actor->padFinish.rows.bRespawnRow,
                                            actor->padFinish.rows.bChainRow);
            actor->dwStateTimer = 16;
        }
        else {
            actor->dwStateTimer = 0;
        }

        if ((actor->dwFlags & ActorFlagRoomScriptYield) && g_bRoomScriptYieldOpcode == RSOP_StartTileActorScript) {
            actor->dwFlags &= ~ActorFlagRoomScriptYield;
            ResumeRoomScriptChain();
            actor->dwStateTimer = 16;
        }
        else if (actor->dwStateTimer != 16) {
            actor->dwStateTimer = 0;
        }
        SetActorActionSubState(actor, 10);
        break;
    case 10:
        if (actor->dwStateTimer != 0) {
            actor->dwStateTimer--;
        }
        else {
            SetActorActionState(actor, 0x21);
            g_dwPauseMenuLocked = 0;
        }
        break;
    }
}

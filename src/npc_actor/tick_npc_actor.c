#include "types.h"
#include "area.h"
#include "color.h"
#include "gen/graphics/overworld.h"
#include "hero.h"
#include "modes.h"
#include "move.h"
#include "overworld/room_script_bytecode.h"
#include "npc_actor.h"

// Standing frame of an eight-way NPC (kind 0x21) for each Direction8 facing,
// in the rows of g_abRoomActorUnk6Frames.
const u8 g_abNpcFacingFrames8[12][8] = {
    { 4, 3, 2, 1, 0, 1, 2, 3 },
    { 2, 2, 1, 1, 0, 0, 1, 1 },
    { 4, 3, 2, 1, 0, 1, 2, 3 },
    { 4, 3, 2, 1, 0, 1, 2, 3 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 3, 2, 1, 0, 1, 2, 3 },
    { 4, 3, 2, 1, 0, 1, 2, 3 },
    { 3, 3, 2, 1, 0, 1, 2, 3 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
};

// pfnTick of an NPC (room actorType 6). Kind 0x21 faces eight ways; kind 0x5F
// has a fixed sprite and, in action state 5, carries the party.
void TickNpcActor(Actor *pActor)
{
    s8 facing = pActor->bFacing;
    u8 kind = pActor->bFighterIndex;
    RoomActorRecordUnk6 *pRecord;

    if (g_GameModeStackContext.dwCurrentGameMode != Overworld
        && g_GameModeStackContext.dwCurrentGameMode != Dialog)
    {
        CancelActorMove_candidate(pActor);
        return;
    }

    if (pActor->timer84.wInteractCooldown != 0)
        pActor->timer84.wInteractCooldown--;

    switch (pActor->bActionState)
    {
    case 0:
        break;
    case 5:
        if (kind == 0x5F && pActor->pOwnerActor == g_pPlayerActor)
        {
            CancelActorMove_candidate(pActor);
            SetActorActionState(pActor, 0);
            SetActorActionSubState(pActor, 2);
            pActor->anim.bAnimFrameCounter = 0;
            pActor->pOwnerActor = NULL;
            if (g_pFollowerActor0 != NULL)
                g_pFollowerActor0->pOwnerActor = NULL;
            if (g_pFollowerActor1 != NULL)
                g_pFollowerActor1->pOwnerActor = NULL;
        }
        break;
    case 3:
        CancelActorMove_candidate(pActor);
        SetActorActionState(pActor, 0);
        SetActorActionSubState(pActor, 2);
        pActor->anim.bAnimFrameCounter = 0;
        if (kind == 0x21)
        {
            if (!(pActor->bFlags_0x94_candidate & 4))
                SetActorAnimFrame(pActor, g_abRoomActorUnk6Frames[g_adwRoomActorUnk6FrameRows[pActor->bFighterIndex]][0]);
            pActor->oam.hFlip = facing > DirectionDown;
        }
        else if (kind != 0x5F)
        {
            if (!(pActor->bFlags_0x94_candidate & 4))
                SetActorAnimFrame(pActor, g_abRoomActorUnk6Frames[g_adwRoomActorUnk6FrameRows[pActor->bFighterIndex]][facing]);
            SetActorFlippedX(pActor, facing == Direction4Left);
        }
        break;
    case 0x16:
        if (pActor->dwFlags & ActorFlagSpecialMoveTrigger)
        {
            pActor->dwFlags &= ~ActorFlagSpecialMoveTrigger;
            if (pActor->bRespawnRow == 9)
                g_nNpcPaletteEffectSlot = StartPaletteEffect(pActor->oam.paletteNum * 16, 16, 2, 0, 0x1D,
                                                             (const u16 *)gActorSprite2_036Palette);
            else if (pActor->bRespawnRow == 10)
                g_nNpcPaletteEffectSlot = StartPaletteEffect(pActor->oam.paletteNum * 16, 16, 2, 0, 0x1D,
                                                             (const u16 *)gActorSprite2_035Palette);
            else if (pActor->bRespawnRow == 12)
                g_nNpcPaletteEffectSlot = StartPaletteEffect(pActor->oam.paletteNum * 16, 16, 2, 0, 0x1D,
                                                             (const u16 *)gActorSprite2_014Palette);
            else if (pActor->bRespawnRow == 4)
                SpawnFieldSpellEffect(pActor, FieldSpellFlipendo);
            else if (pActor->bRespawnRow == 8)
            {
                pActor->bFacing = 6;
                SpawnFieldSpellEffect(pActor, FieldSpellReparo);
                CancelActorMove_candidate(pActor);
            }
        }
        else if (pActor->dwFlags & ActorFlagActionAnimDone)
        {
            if (pActor->bRespawnRow == 8)
                pActor->bFacing = 3;
            pActor->dwFlags &= ~ActorFlagActionAnimDone;
            StopPaletteEffect(g_nNpcPaletteEffectSlot);
            SetActorActionState(pActor, 0);
            if ((pActor->dwFlags & ActorFlagRoomScriptYield)
                && g_bRoomScriptYieldOpcode == RSOP_PlayTileActorAnimation)
            {
                pActor->dwFlags &= ~ActorFlagRoomScriptYield;
                ResumeRoomScriptChain();
            }
        }
        break;
    case 4:
        pRecord = GetRoomActorStaticRecord(pActor->bRoomTileCol_candidate, pActor->bRoomTileRow_candidate);
        if (pActor->bRoomActorKind_candidate == 1)
        {
            pActor->timer84.wInteractCooldown = pRecord->wInteractCooldown * 30;
            pActor->bFlags_0x94_candidate &= ~1;
        }
        SetActorActionState(pActor, pActor->bPrevActionState_candidate);
        RespawnGroupAndRunChain(pRecord->argC.bytes.bRespawnRow, pRecord->argC.bytes.bChainRow);
        pActor->dwFlags |= ActorFlagHasAnimation;
        break;
    default:
        TickActorActionState(pActor);
        break;
    }

    facing = pActor->bFacing;
    if (pActor->bActionFlags & 0x12)
    {
        if (pActor->bActionSubState == 3)
        {
            if (kind == 0x5F && pActor->pOwnerActor != g_pPlayerActor)
            {
                pActor->pOwnerActor = g_pPlayerActor;
                if (g_pFollowerActor0 != NULL)
                    g_pFollowerActor0->pOwnerActor = g_pPlayerActor;
                if (g_pFollowerActor1 != NULL)
                    g_pFollowerActor1->pOwnerActor = g_pPlayerActor;
            }

            SetActorVelocityFromFacing(pActor);
            if (!(pActor->bFlags_0x94_candidate & 4))
            {
                if (kind == 0x21)
                    SetActorAnimData(pActor, &g_aActorTypeAssets[kind],
                                     g_aaabNpcWalkAnims[g_adwRoomActorUnk6FrameRows[kind]][0], 0);
                else if (kind != 0x5F)
                    SetActorAnimData(pActor, &g_aActorTypeAssets[kind],
                                     g_aaabNpcWalkAnims[g_adwRoomActorUnk6FrameRows[kind]][facing], 0);
            }
        }
        else if (pActor->bActionSubState == 10 || pActor->bActionSubState == 2
                 || (pActor->vel.x == 0 && pActor->vel.y == 0))
        {
            CancelActorMove_candidate(pActor);
            if (!(pActor->bFlags_0x94_candidate & 4))
            {
                if (kind == 0x21)
                {
                    SetActorAssetRecord(pActor, &g_aActorTypeAssets[kind]);
                    SetActorAnimFrame(pActor, g_abNpcFacingFrames8[g_adwRoomActorUnk6FrameRows[kind]][facing]);
                }
                else if (kind != 0x5F)
                {
                    SetActorAssetRecord(pActor, &g_aActorTypeAssets[kind]);
                    SetActorAnimFrame(pActor, g_abRoomActorUnk6Frames[g_adwRoomActorUnk6FrameRows[kind]][facing]);
                }
            }
        }

        pActor->bActionFlags = 0;
        if (kind == 0x21)
            pActor->oam.hFlip = facing > DirectionDown;
        else if (kind != 0x5F)
            SetActorFlippedX(pActor, facing == Direction4Left);
    }
}

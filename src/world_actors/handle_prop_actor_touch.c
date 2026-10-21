#include "types.h"
#include "actor.h"
#include "area.h"
#include "hero.h"
#include "input.h"
#include "move.h"
#include "particles.h"
#include "scroll.h"
#include "sound.h"
#include "world_actors.h"
#include "gen/graphics/overworld.h"

// Collision box 0. The player presses A at kinds 68 and 80, or rebreaks a prop that Reparo is
// restoring by standing on it. Flipendo pushes a pushable prop (stopped at the screen edge)
// or breaks a breakable one, Reparo restores it, Glacius and Diffindo trigger their kinds.
// Two pushed props stop each other unless one has bFighterIndex 4.
void HandlePropActorTouch(Actor *pSelf, Actor *pOther)
{
    u8 kind;
    u16 spell;
    s32 camera[2];
    IntPoint screen;

    if (pSelf->dwFlags & ActorFlagNoPushTrigger_candidate)
        return;
    if (pOther->dwFlags & ActorFlagNoPushTrigger_candidate)
        return;

    kind = ROOM_ACTOR_TRIGGER_STATE(pSelf)->bKind;

    switch (pOther->wActorType)
    {
    case 4:  // trigger zones handle prop contact themselves
        break;
    case RoomActorType_Player:
        if (pOther->bActionState != 0x21)
            break;

        if (kind == 80 && (g_wKeysPressed & KeyA))
        {
            SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
            SetActorActionState(pSelf, 4);
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        }
        else if (kind == 68 && (g_wKeysPressed & KeyA))
        {
            SetActorActionState(pSelf, 4);
            pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
        }
        else if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBreakable != 0
                 && ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame > 80
                 && pOther->pos.x == pOther->posPrev.x && pOther->pos.y == pOther->posPrev.y
                 && DoActorsOverlap(pSelf, pOther))
        {
            if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame != 0xFF)
                SetActorAnimFrame(pSelf, ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame - 80);
            BreakPropActor(pSelf);
        }
        break;
    case RoomActorType_ScriptedTrigger:
        if (pSelf->bFighterIndex == 4 || pOther->bFighterIndex == 4)
            break;
        pSelf->posPrev.x = pSelf->pos.x;
        pSelf->posPrev.y = pSelf->pos.y;
        pOther->posPrev.x = pOther->pos.x;
        pOther->posPrev.y = pOther->pos.y;
        pSelf->vel.x = 0;
        pSelf->vel.y = 0;
        pOther->vel.x = 0;
        pOther->vel.y = 0;
        break;
    case RoomActorType_FieldSpellEffect:
        spell = pOther->wCharacterId_candidate;
        switch (spell)
        {
        case FieldSpellFlipendo:
            if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame != 0xFF)
                break;

            if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bPushable != 0)
            {
                if (kind == 57 && pOther->bFacing == DirectionLeft)
                {
                    ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame = pSelf->anim.bLastAnimFrameValue;
                    SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
                    ROOM_ACTOR_TRIGGER_STATE(pSelf)->bPushable = 0;
                    if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow != 0)
                        RespawnGroupAndRunChain(0, ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow);
                    break;
                }

                if (kind == 39 || kind == 43)
                {
                    SetActorActionState(pSelf, 4);
                    pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
                    HandleFieldSpellHit(pOther, pSelf);
                }
                else
                {
                    GetCameraPosition(camera);
                    screen.x = (s16)(pSelf->pos.x >> 16) - camera[0];
                    screen.y = (s16)(pSelf->pos.y >> 16) - camera[1];
                    if (pSelf->spriteBounds.edges.wLeft + screen.x < 0
                        || pSelf->spriteBounds.edges.wRight + screen.x > 240
                        || pSelf->spriteBounds.edges.wTop + screen.y < 0
                        || pSelf->spriteBounds.edges.wBottom + screen.y > 160)
                    {
                        pSelf->vel.x = 0;
                        pSelf->vel.y = 0;
                    }
                    else
                    {
                        PlaySoundById(0x21);
                        pSelf->vel.x = g_aRoomActorTriggerPushVelocity[pOther->bFacing][0] << 16;
                        pSelf->vel.y = g_aRoomActorTriggerPushVelocity[pOther->bFacing][1] << 16;
                    }
                    pSelf->bFacing = g_adwRoomActorTriggerPushFacing[pOther->bFacing];
                    HandleFieldSpellHit(pOther, pSelf);
                }
            }
            else if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBreakable != 0)
            {
                BreakPropActor(pSelf);
            }
            break;
        case FieldSpellReparo:
            if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame != 0xFF)
            {
                if (pSelf->bActionState == 2 || ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBreakable == 0)
                    break;

                if (kind == 0)
                {
                    LoadParticleGfx(1, 0, (const ActorAssetRecord *)&g_RoomPropParticleGfx0);
                    LoadParticleGfx(1, 1, (const ActorAssetRecord *)&g_RoomPropParticleGfx1);
                    LoadParticleGfx(1, 2, (const ActorAssetRecord *)&g_RoomPropParticleGfx2);
                }
                else
                {
                    LoadParticleGfx(1, 0, (const ActorAssetRecord *)&g_RoomPropParticleGfx3);
                    LoadParticleGfx(1, 1, (const ActorAssetRecord *)&g_RoomPropParticleGfx4);
                    LoadParticleGfx(1, 2, (const ActorAssetRecord *)&g_RoomPropParticleGfx5);
                }
                PlaySoundById(0x20);
                InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 0), pSelf);
                InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 1), pSelf);
                InitPropBreakEmitter(AllocParticleEmitter((const ObjPalette *)gOverworldSpellEffect027Palette, 1, 2), pSelf);
                pSelf->dwStateTimer = 16;
                ROOM_ACTOR_TRIGGER_STATE(pSelf)->bBrokenFrame += 80;
                SetActorActionState(pSelf, 2);
            }
            else if (kind == 53)
            {
                SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
                SetActorActionState(pSelf, 0);
                pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
            }
            break;
        case FieldSpellDiffindo:
            if (kind == 46 || kind == 47 || kind == 48 || kind == 49 || kind == 50 || kind == 54 || kind == 77)
            {
                SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 2);
                SetActorActionState(pSelf, 2);
                pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
                HandleFieldSpellHit(pOther, pSelf);
            }
            else
            {
                HandleFieldSpellHit(pOther, pSelf);
            }
            break;
        case FieldSpellGlacius:
            if (kind == 51)
            {
                MarkRoomActorConsumed(pSelf);
            }
            else if (kind == 76)
            {
                SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 7);
                SetActorActionState(pSelf, 0);
                pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
                if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow != 0)
                    RespawnGroupAndRunChain(0, ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow);
            }
            else if (kind == 52)
            {
                SetActorAnimData(pSelf, g_apRoomActorTriggerAnimFrames[kind], g_abRoomActorTriggerAnimData[kind], 12);
                SetActorActionState(pSelf, 0);
                pSelf->dwFlags &= ~ActorFlagWantsCollisionCheck;
                if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow != 0)
                    RespawnGroupAndRunChain(0, ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow);
            }
            else if (kind == 63)
            {
                if (ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow != 0)
                    RespawnGroupAndRunChain(0, ROOM_ACTOR_TRIGGER_STATE(pSelf)->bChainRow);
            }
            HandleFieldSpellHit(pOther, pSelf);
            break;
        }
        break;
    }
}

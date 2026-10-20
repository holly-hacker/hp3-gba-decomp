#pragma once

#include "types.h"
#include "actor.h"

typedef struct RoomActorRecordUnk6 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bKind;               // 0x08, index into the asset tables
    u8 bFacing;             // 0x09, stored halved
    u16 wInteractCooldown;  // 0x0A, in units of 30 ticks
    union {
        u32 dwWord;         // bytes 1 and 2 are tested as a pair: zero is not interactable
        struct {
            u8 bInteractMode;   // 0: interactable once, 1: again after the cooldown
            u8 bRespawnRow;     // RespawnGroupAndRunChain arguments run on interaction
            u8 bChainRow;
        } bytes;
    } argC;                 // 0x0C
} RoomActorRecordUnk6;

extern Actor *SpawnNpcActor(u8 bColumn, u8 bRow);
extern Actor *SpawnCharacterNpcActor(u8 characterId);
extern void TickNpcActor(Actor *pActor);
extern void HandleNpcActorTouch(Actor *pSelf, Actor *pOther);
extern Actor *SpawnShadowActor(Actor *pOwner);
extern void StartNpcScriptAnimation(Actor *pActor, u16 animId);
extern void TickShadowActor(Actor *pShadow);

extern s32 g_nNpcPaletteEffectSlot;  // StartPaletteEffect handle of a script animation's flash

extern const u32 g_adwRoomActorUnk6FrameRows[110];      // ROM 0x08066E44 (US)
extern const ActorAssetRecord g_aActorTypeAssets[137];  // ROM 0x08066FFC (US), indexed by an actor kind
extern const u8 g_abRoomActorUnk6Frames[12][4];         // ROM 0x0806788C (US)
extern const u8 g_aaabNpcWalkAnims[12][4][30];          // ROM 0x080678BC (US)
extern const u8 g_aabNpcScriptAnims[27][128];           // ROM 0x08067E5C (US)
extern const u8 g_abCharacterNpcKinds[12];              // ROM 0x08068BDC (US)
extern const ActorGfxRecord g_ShadowActorGfx;           // ROM 0x08068BE8 (US)
extern const u8 g_abNpcFacingFrames8[12][8];            // ROM 0x08FAAE98 (US)

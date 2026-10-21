#pragma once

#include "types.h"
#include "actor.h"

// The chest, room actor type 9; see docs/formats/rooms.md.

// Chest record. wFlagId is the chest's bit in g_abOpenedChestFlags.
typedef struct RoomActorRecordChest {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u16 wFlagId;        // 0x08
    u8 bKind;           // 0x0A, 0-3; 2 despawns once opened
    u8 bRewardId;       // 0x0B, see rewards.h; above REWARD_ID_GOLD runs the pair instead
    u8 bChain;          // 0x0C
    u8 bRespawnGroup;   // 0x0D
} RoomActorRecordChest;

// One bit per chest flag id, set when that chest is opened. Saved with the game.
extern u8 g_abOpenedChestFlags[32];

extern const ActorGfxRecord g_RoomChestSprite;                  // ROM 0x0804D524 (US)
extern const ActorGfxRecord *const g_apRoomChestAnimFrames[4];  // ROM 0x0804D52C (US)
extern const u8 g_abRoomChestAnimData[4][100];                   // ROM 0x0804D53C (US)

extern Actor *SpawnChestActor(u8 bColumn, u8 bRow);
extern void TickChestActor(Actor *pActor);
extern void HandleChestTouch(Actor *pSelf, Actor *pOther);

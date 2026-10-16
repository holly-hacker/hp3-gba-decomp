#pragma once

#include "types.h"

typedef struct {
    const void *pFloor;  // graphic blob, see docs/formats/graphic_blob.md
    const void *pWall;
} BattleBackgroundPair;
extern const BattleBackgroundPair g_aBattleBackgroundPairs[55];  // 0x0804E09C, indexed by g_bCurrentRoomId

extern const u8 g_abBattleMusicByRoom[55];          // 0x0804E254, indexed by g_bCurrentRoomId
extern const u8 g_abBattleMusicByScriptedEncounter[15]; // 0x0804E28B, indexed by dwCurrentGameModeArg1 (scripted encounter id)

#pragma once

#include "types.h"
#include "actor.h"
#include "gen/graphics/menus.h"

typedef struct {
    Actor *pCursorActor;  // 0x00
    u32 dwSelection;        // 0x04: row of the cheat menu
} CheatState;

extern CheatState g_CheatState;  // 0x030021C0
extern const u32 g_dwCheatBg0Control;  // 0x0804C444
extern const u32 g_dwCheatBg1Control;  // 0x0804C448
extern const ActorAssetRecord g_CheatAnimFrames;  // 0x0804C44C
extern const u8 g_CheatAnimData[18];    // 0x0804C45C

extern void ResetCheatPartyFromArgs_candidate(void);
extern void DrawCheatEntries_candidate(void);

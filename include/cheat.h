#pragma once

#include "types.h"
#include "actor.h"

typedef struct {
    Actor *pCursorActor;  // 0x00
    u32 dwSelection;        // 0x04: row of the cheat menu
} CheatState;

extern CheatState g_CheatState;  // 0x030021C0
extern const u32 g_dwCheatBg0Control;
extern const u32 g_dwCheatBg1Control;
extern const ActorAssetRecord g_CheatAnimFrames;
extern const u8 g_CheatAnimData[18];

extern void InitializeCheat(void);
extern void UpdateCheat(void);
extern void ExitCheat(void);

extern void ResetCheatPartyFromArgs(void);
extern void DrawCheatEntries(void);

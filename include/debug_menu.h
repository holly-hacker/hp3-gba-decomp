#pragma once

#include "types.h"
#include "object.h"

typedef struct {
    Object *pCursorObject;  // 0x00
    u32 dwSelection;        // 0x04: row of the debug main menu
} DebugMenuMainState;

extern DebugMenuMainState g_DebugMenuMainState;  // 0x030021C0

extern const u32 g_dwDebugMenuMainBg0Control;  // 0x0804C444
extern const u32 g_dwDebugMenuMainBg1Control;  // 0x0804C448
extern const u8 g_DebugMenuGraphic[];          // 0x08D9A360
extern const u8 g_DebugMenuCursorSpawnData[];  // 0x080BC538
extern const u8 g_DebugMenuMainAnimFrames[];   // 0x0804C44C
extern const u8 g_DebugMenuMainAnimData[];     // 0x0804C45C

extern Object *SpawnObject(u32 type, s32 x, s32 y, const void *pData);
extern void ResetCharacterToLevel(u32 character, u32 level);
extern void InitCharacterSpells_candidate(u32 index, u16 *pStats);
extern void ResetDebugPartyFromArgs_candidate(void);
extern void DrawDebugMenuMainEntries_candidate(void);
extern u32 StepWrappedSelectionVertical_candidate(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);

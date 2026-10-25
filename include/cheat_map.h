#pragma once

#include "types.h"
#include "actor.h"

typedef struct {
    Actor *pCursorActor;  // 0x00
    u32 dwCursorRow;        // 0x04: visible row, 0..0x11
    s32 nScrollY;           // 0x08: BG1 vertical scroll in pixels; the map index is nScrollY / 8 + dwCursorRow
} CheatMapState;

extern CheatMapState g_CheatMapState;  // 0x030021E8
extern const u32 g_dwCheatMapBg0Control;
extern const u32 g_dwCheatMapBg1Control;
extern const ActorAssetRecord g_CheatMapAnimFrames;
extern const u8 g_CheatMapAnimData[18];

extern void InitializeCheatMap(void);
extern void UpdateCheatMap(void);
extern void ExitCheatMap(void);

extern void DrawCheatMapNames(void);
extern void ScrollCheatMap(u32 scrollUp);

#pragma once

#include "types.h"

// Battle screen scanline callbacks, listed in g_aBattleScanlineEffects.
extern void EndBattleWallScanline(u32 *pPayload0, u32 *pPayload1);
extern void BeginBattleHudScanline(u32 *pPayload0, u32 *pPayload1);
extern void RestoreBattleHudPanelTilemap(u32 *pPayload0, u32 *pPayload1);
// No callers. Draws a battle message line at y, right half when align bit 0 is set.
extern void DrawBattleMessageLine_unused(s32 textId, s32 y, u32 align);

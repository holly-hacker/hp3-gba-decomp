#pragma once

#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "mem.h"
#include "video.h"

// The body of sub_08012A00, which InitBattleDisplay compiles inline: queues the battle
// scanline effects with the BG1 wall band ending at FightState.bWallEndLine.
static inline void QueueBattleScanlineEffects(void)
{
    CopyMemory(g_aBattleScanlineEffectBuffer, g_aBattleScanlineEffects, sizeof(g_aBattleScanlineEffectBuffer));
    g_aBattleScanlineEffectBuffer[1].wLine = g_pFightState->bWallEndLine;
    QueueScanlineEffectTable(g_aBattleScanlineEffectBuffer, 4);
}

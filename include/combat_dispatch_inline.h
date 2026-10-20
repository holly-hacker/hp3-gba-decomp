#pragma once

#include "color.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"
#include "combat_gauge.h"
#include "hw/io_regs.h"
#include "mem.h"
#include "video.h"

// The body of RestoreBattleScanlineEffects, which InitBattleDisplay compiles inline: queues the battle
// scanline effects with the BG1 wall band ending at FightState.bWallEndLine.
static inline void QueueBattleScanlineEffects(void)
{
    CopyMemory(g_aBattleScanlineEffectBuffer, g_aBattleScanlineEffects, sizeof(g_aBattleScanlineEffectBuffer));
    g_aBattleScanlineEffectBuffer[1].wLine = g_pFightState->bWallEndLine;
    QueueScanlineEffectTable(g_aBattleScanlineEffectBuffer, 4);
}

// The body of StopEnemyTargetFlash and its siblings, which the target menu handlers compile
// inline: waits for scanline 42, then ends the target flash palette effect.
static inline void StopTargetFlash(void)
{
    while (REG_VCOUNT != 42) {
        while (!(REG_DISPSTAT & DISPSTAT_HBLANK))
            ;
    }

    CompletePaletteEffect(g_pFightState->nTargetFlashEffect);
}

// The body of WrapBattleMenuCursor: a cursor stepped past lastRow wraps to 0, one stepped
// below 0 (a u8 underflow) wraps to lastRow.
static inline u32 WrapMenuCursor(u32 cursor, u32 lastRow)
{
    lastRow++;
    if (cursor > lastRow)
        cursor = lastRow - 1;
    else if (cursor == lastRow)
        cursor = 0;

    return cursor;
}

// FighterHasShadowActor, in the form the camera zoom functions compile inline.
static inline s32 HasShadowActor(u32 fighterIndex)
{
    u32 monsterId;

    // Monster actor types follow the four party FighterTypes.
    monsterId = g_pFightState->pFighters[fighterIndex].pActor->wActorType - 4;
    if (IS_SALAMANDER(monsterId))
        return 1;

    return 0;
}

// OpenEnemyTargetMenu, in the form the menu confirm handlers compile inline.
static inline void ShowEnemyTargetMenu(u8 fighterIndex)
{
    ZoomBattleCameraIn();
    g_pFightState->bMenuScreen = BattleMenuEnemyTarget;
    ClearBattleTextPanel();
    DrawFighterStatsUi(g_pFightState->pFighters[fighterIndex].bFighterType, 0);
    g_pFightState->bMenuCursor = 0;
    MoveEnemyTargetCursor(1);
    SpawnSpGauge(g_pFightState->aEnemySlotTurnOrderIndex[g_pFightState->bMenuCursor], 0);
    FlashEnemyTarget(g_pFightState->bMenuCursor);
}

// Opens the fighter's spell list with the cursor on row.
static inline void ShowSpellChoiceMenu(u8 fighterIndex, u32 row)
{
    BattleFighter *fighter;
    u32 i;

    fighter = &g_pFightState->pFighters[fighterIndex];
    g_pFightState->bMenuScreen = BattleMenuSpellChoice;
    ClearBattleTextPanel();
    DrawBattleMenuFrame();
    DrawFighterStatsUi(fighter->bFighterType, 0);

    for (i = 0; i < fighter->stats.bKnownSpellCount; i++)
        SetBattleMenuIconState(1, i, fighter->bFighterType, 1);

    g_pFightState->bMenuCursor = row;
    SelectBattleMenuIcon(g_pFightState->bMenuCursor);
    DrawBattleMenuText();
}

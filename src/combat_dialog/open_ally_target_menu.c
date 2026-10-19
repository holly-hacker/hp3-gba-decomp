#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_gauge.h"
#include "interrupts.h"
#include "modes.h"
#include "mode7.h"

// Opens the ally target menu after letting the battle run for eight frames, with the cursor
// on the first occupied ally slot.
void OpenAllyTargetMenu(u8 fighterIndex)
{
    u8 i;

    i = 1;
    do {
        WaitForVBlankIntr();
        WaitForVBlankIntr();
        UpdateFloorAffineTable();
        TickFrameSystems();
    } while (i++ < 8);

    g_pFightState->bMenuScreen = BattleMenuAllyTarget;
    ClearBattleTextPanel();
    DrawFighterStatsUi(g_pFightState->pFighters[fighterIndex].bFighterType, 0);
    // The active fighter's index is stored and at once replaced.
    g_pFightState->bMenuCursor = g_pFightState->bActiveFighterIndex;
    g_pFightState->bMenuCursor = 0;
    MoveAllyTargetCursor(1);
    SpawnSpGauge(g_pFightState->aAllySlotTurnOrderIndex[g_pFightState->bMenuCursor], 0);
    FlashAllyTarget(g_pFightState->bMenuCursor);
    DrawAllyTargetStats(g_pFightState->bMenuCursor);
}

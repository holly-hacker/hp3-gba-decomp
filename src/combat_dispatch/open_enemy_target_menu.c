#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_gauge.h"

// Zooms the camera in and opens the enemy target menu with the cursor on the first occupied
// enemy slot.
void OpenEnemyTargetMenu(u8 fighterIndex)
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

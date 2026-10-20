#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "combat_gauge.h"
#include "items.h"
#include "sound.h"

// Targets the ally slot on the cursor and closes the menu. A potion is used up here.
void ConfirmAllyTargetMenu(u32 fighterType, BattleFighter *pFighter)
{
    StopTargetFlash();
    DestroySlotSpGauge(g_pFightState->bMenuCursor, 1);
    DrawFighterStatsUi(g_pFightState->pFighters[g_pFightState->bMenuFighterIndex].bFighterType, 0);
    PlaySoundById(1);
    pFighter->bSelectedActionIndex = g_pFightState->bMenuCursor;
    g_pFightState->bMenuScreen = BattleMenuNone;
    if (pFighter->bPendingActionKind == PendingActionUsePotion)
        RemoveItems(g_dwBattleItemToConsume, 1);
}

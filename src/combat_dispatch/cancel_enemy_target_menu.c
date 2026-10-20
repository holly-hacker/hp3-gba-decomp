#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "combat_gauge.h"

// Zooms back out and reopens the menu that led to the enemy target menu.
void CancelEnemyTargetMenu(u32 fighterType, BattleFighter *pFighter)
{
    u8 fighterIndex;

    StopTargetFlash();
    DestroySlotSpGauge(g_pFightState->bMenuCursor, 0);
    ZoomBattleCameraOut();

    if (pFighter->bPendingActionKind == PendingActionSpecialMove) {
        fighterIndex = g_pFightState->bMenuFighterIndex;
        if (g_pFightState->pFighters[fighterIndex].bFighterType == Harry)
            OpenBattleTopMenu(fighterIndex, 1);  // Special Move
        else
            OpenSpecialMoveMenu(fighterIndex);
    } else if (pFighter->bPendingActionKind == PendingActionNone) {
        OpenSpellTierMenu(g_pFightState->bMenuFighterIndex, g_pFightState->bSpellMenuCursor);
    } else if (pFighter->bPendingActionKind == PendingActionUsePotion) {
        OpenItemMenu(g_pFightState->bMenuFighterIndex);
    } else if (pFighter->bPendingActionKind == PendingActionInformus) {
        OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, 2);  // Informus
    }
}

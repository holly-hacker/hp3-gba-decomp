#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "combat_gauge.h"

// Reopens the menu that led to the ally target menu.
void CancelAllyTargetMenu(u32 fighterType, BattleFighter *pFighter)
{
    u8 fighterIndex;

    StopTargetFlash();
    DestroySlotSpGauge(g_pFightState->bMenuCursor, 1);

    if (pFighter->bPendingActionKind == PendingActionSpecialMove) {
        fighterIndex = g_pFightState->bMenuFighterIndex;
        if (g_pFightState->pFighters[fighterIndex].bFighterType == Harry)
            OpenBattleTopMenu(fighterIndex, 1);  // Special Move
        else
            OpenSpecialMoveMenu(fighterIndex);
    } else if (pFighter->bPendingActionKind == PendingActionNone) {
        ShowSpellChoiceMenu(g_pFightState->bMenuFighterIndex, g_pFightState->bSpellMenuCursor);
    } else if (pFighter->bPendingActionKind == PendingActionUsePotion) {
        OpenItemMenu(g_pFightState->bMenuFighterIndex);
    }
}

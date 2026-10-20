#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "items.h"
#include "sound.h"

// Takes the potion on the cursor row, if the party has one, and opens the ally target menu.
// Battle item row n is item id n + 0x38.
void ConfirmItemMenu(u32 fighterType, BattleFighter *pFighter)
{
    if (IsBattleItemSlotUsable(g_pFightState->bMenuCursor)) {
        pFighter->bPendingActionKind = PendingActionUsePotion;
        pFighter->bSpellLevel = g_pFightState->bMenuCursor + 0x38;
        g_dwBattleItemToConsume = g_pFightState->bMenuCursor + 0x38;
        OpenAllyTargetMenu(g_pFightState->bMenuFighterIndex);
    } else {
        PlaySoundById(3);
    }
}

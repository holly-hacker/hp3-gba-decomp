#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"

void CancelToBattleTopMenu(u32 fighterType, BattleFighter *pFighter)
{
    u32 row;

    row = 0;
    switch (g_pFightState->bMenuScreen) {
    case BattleMenuSpellChoice:
        row = 0;  // Cast Spell
        break;

    case BattleMenuItem:
        row = 3;  // Use Item
        break;

    case BattleMenuSpecialMove:
        row = 1;  // Special Move
        break;
    }

    OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, row);
}

#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "items.h"

// Opens the six-row battle item menu, graying the slots that can't be used.
void OpenItemMenu(u8 fighterIndex)
{
    u8 fighterType;
    s32 i;

    fighterType = g_pFightState->pFighters[fighterIndex].bFighterType;
    g_pFightState->bMenuScreen = BattleMenuItem;
    ClearBattleTextPanel();
    DrawBattleMenuFrame();
    DrawFighterStatsUi(fighterType, 0);

    for (i = 0; i < 6; i++) {
        if (IsBattleItemSlotUsable(i))
            SetBattleMenuIconState(2, i, fighterType, 1);
        else
            SetBattleMenuIconState(2, i, fighterType, 0);
    }

    g_pFightState->bMenuCursor = 0;
    SelectBattleMenuIcon(g_pFightState->bMenuCursor);
    DrawBattleMenuText();
}

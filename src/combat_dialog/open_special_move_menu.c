#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"

// Opens Hermione's or Ron's three-row Special Move menu.
void OpenSpecialMoveMenu(u8 fighterIndex)
{
    u8 fighterType;
    u32 i;

    g_pFightState->bMenuScreen = BattleMenuSpecialMove;
    ClearBattleTextPanel();
    DrawBattleMenuFrame();
    DrawFighterStatsUi(g_pFightState->pFighters[fighterIndex].bFighterType, 0);

    fighterType = g_pFightState->pFighters[fighterIndex].bFighterType;
    for (i = 0; i < 3; i++)
        SetBattleMenuIconState(3, i, fighterType, 1);

    g_pFightState->bMenuCursor = 0;
    SelectBattleMenuIcon(g_pFightState->bMenuCursor);
    DrawBattleMenuText();
    g_pFightState->pFighters[fighterIndex].bSelectedActionIndex = 0xFF;
}

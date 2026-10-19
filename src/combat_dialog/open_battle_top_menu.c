#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "modes.h"
#include "random.h"

// Opens the top battle menu for fighterIndex with the cursor on row. Special Move is grayed
// once Hermione or Ron has used theirs, Informus and Flee in scripted encounters. Buckbeak
// gets no menu: he attacks a random live fighter.
void OpenBattleTopMenu(u32 fighterIndex, u32 row)
{
    u8 targetIndex;
    u8 fighterType;
    u32 enabled[7];
    u32 i;

    if (g_pFightState->pFighters[fighterIndex].bFighterType == Buckbeak) {
        g_pFightState->pFighters[fighterIndex].bPendingActionKind = PendingActionNone;
        do {
            targetIndex = Mt19937RandMax(6);
        } while (g_pFightState->pFighters[targetIndex].bFighterType == Enemy
                 || g_pFightState->pFighters[targetIndex].pActor == NULL
                 || g_pFightState->pFighters[targetIndex].stats.wHp == 0);
        g_pFightState->pFighters[fighterIndex].bSelectedActionIndex = targetIndex;
        return;
    }

    fighterType = g_pFightState->pFighters[fighterIndex].bFighterType;
    g_pFightState->bMenuScreen = BattleMenuTop;
    ClearBattleTextPanel();
    DrawBattleMenuFrame();
    DrawFighterStatsUi(g_pFightState->pFighters[fighterIndex].bFighterType, 0);

    for (i = 0; i < 7; i++)
        enabled[i] = 1;

    if ((fighterType == Hermione && g_pFightState->dwHermioneSpecialUsed)
        || (fighterType == Ron && g_pFightState->dwRonSpecialUsed))
        enabled[1] = 0;  // Special Move

    // 0xFF: a scripted battle.
    if (g_dwPendingGameMode.dwCurrentGameModeArg3 == 0xFF) {
        enabled[2] = 0;  // Informus
        enabled[4] = 0;  // Flee
    }

    for (i = 0; i < 7; i++)
        SetBattleMenuIconState(0, i, fighterType, enabled[i]);

    g_pFightState->bMenuCursor = row;
    SelectBattleMenuIcon(g_pFightState->bMenuCursor);
    DrawBattleMenuText();
    g_pFightState->pFighters[fighterIndex].bSelectedActionIndex = 0xFF;
}

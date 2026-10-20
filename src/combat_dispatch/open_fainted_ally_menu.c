#include "types.h"
#include "combat.h"
#include "combat_board.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "interrupts.h"
#include "modes.h"
#include "mode7.h"

// Opens the pending fighter menu after letting the battle run for eight frames, with the
// cursor on the first pending fighter.
void OpenFaintedAllyMenu(u8 fighterIndex)
{
    u8 i;

    i = 1;
    do {
        WaitForVBlankIntr();
        WaitForVBlankIntr();
        UpdateFloorAffineTable();
        TickFrameSystems();
    } while (i++ < 8);

    g_pFightState->bMenuScreen = BattleMenuFaintedAlly;
    ClearBattleTextPanel();
    DrawFighterStatsUi(g_pFightState->pFighters[fighterIndex].bFighterType, 0);
    g_pFightState->bMenuCursor = 0;
    FlashFaintedAlly(g_pFightState->bMenuCursor);
}

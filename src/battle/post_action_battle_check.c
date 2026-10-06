#include "types.h"
#include "battle/battle.h"

// Runs after a fighter's action resolves: checks for party defeat and, unless
// that ended the battle, returns the state machine to state 1 (next fighter),
// rebuilding the turn order first if a fighter was just knocked out.
void PostActionBattleCheck(void)
{
    g_pFightState->dwPlayerActionActive_candidate = 0;
    CheckBattleDefeat();

    if (g_GameModeStackContext.dwCurrentGameModeArg3 != 0xFE) {
        PushBattleState(1);

        if (g_pFightState->dwDefeatCheckPending_candidate) {
            g_pFightState->dwDefeatCheckPending_candidate = 0;
            PruneFaintedAndRebuildTurnOrder_candidate(0);
        }
    }
}

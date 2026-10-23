#include "combat_dispatch.h"
#include "combat_fighter.h"
#include "combat.h"
#include "modes.h"

// Runs after a fighter's action resolves: checks for party defeat and, unless
// that ended the battle, returns the state machine to BattleStateNextTurn,
// rebuilding the turn order first if a fighter was just knocked out.
void PostActionBattleCheck(void)
{
    g_pFightState->dwBattleMessageShown = 0;
    CheckBattleDefeat();

    if (g_GameModeStackContext.dwCurrentGameModeArg3 != 0xFE) {
        PushBattleState(BattleStateNextTurn);

        if (g_pFightState->dwFighterFainted) {
            g_pFightState->dwFighterFainted = 0;
            PruneFaintedAndRebuildTurnOrder(0);
        }
    }
}

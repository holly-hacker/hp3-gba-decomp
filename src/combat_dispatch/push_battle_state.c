#include "types.h"
#include "combat_dispatch.h"
#include "combat.h"

// Switches the battle turn state machine to `state`, remembering the current
// state in bSavedBattleState. Ignored while the battle is already ending
// (BattleStateDefeat and BattleStateVictory).
void PushBattleState(s32 state)
{
    if (g_pFightState->bBattleState != BattleStateDefeat && g_pFightState->bBattleState != BattleStateVictory) {
        g_pFightState->bSavedBattleState = g_pFightState->bBattleState;
        g_pFightState->bBattleState = state;
        g_pFightState->dwStateJustEntered = 1;
    }
}

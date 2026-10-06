#include "types.h"
#include "battle/battle.h"

// Switches the battle turn state machine to `state`, remembering the current
// state in bSavedBattleState. Ignored while the battle is already ending
// (states 6 and 7).
void PushBattleState(s32 state)
{
    if (g_pFightState->bBattleState != 6 && g_pFightState->bBattleState != 7) {
        g_pFightState->bSavedBattleState = g_pFightState->bBattleState;
        g_pFightState->bBattleState = state;
        g_pFightState->dwStateJustEntered = 1;
    }
}

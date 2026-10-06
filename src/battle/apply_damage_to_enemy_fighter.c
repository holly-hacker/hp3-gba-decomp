#include "types.h"
#include "battle/battle.h"
#include "game/rewards.h"

#define FIGHTER(i) (g_pFightState->pFighters[i])

// Applies a player attack's damage to an enemy. At 0 HP (or on HP underflow)
// the enemy faints: its roster index is queued in g_anFaintedRosterIndices,
// its XP and gold are added to the battle rewards, and its Object enters
// action state 1. Unlike ApplyDamageToAllyFighter, this does not strip the
// critical-hit sentinel from the damage.
void ApplyDamageToEnemyFighter(s32 damage, s32 fighterIndex)
{
    s32 slot;

    FIGHTER(fighterIndex).wHp -= damage;

    if (FIGHTER(fighterIndex).wHp == 0 || FIGHTER(fighterIndex).wHp > FIGHTER(fighterIndex).wHp_max) {
        g_pFightState->dwDefeatCheckPending_candidate = 1;

        if (g_pFightState->bFaintMessageCount_candidate == 0)
            ShowBattleMessage(AttackResult, (u16)fighterIndex, 2);

        slot = 0;
        if (g_anFaintedRosterIndices[0] != -1) {
            do {
                slot++;
                if (slot > 3)
                    break;
            } while (g_anFaintedRosterIndices[slot] != -1);
        }

        g_anFaintedRosterIndices[slot] = FIGHTER(fighterIndex).bRosterIndex;
        g_nBattleXpReward = MonsterTable[FIGHTER(fighterIndex).bRosterIndex].wRewardXp + g_nBattleXpReward;
        g_nBattleGoldReward = MonsterTable[FIGHTER(fighterIndex).bRosterIndex].wRewardGold + g_nBattleGoldReward;
        FIGHTER(fighterIndex).wHp = 0;
        FIGHTER(fighterIndex).nFaintedFlag = -1;
        SetObjectActionState(FIGHTER(fighterIndex).pObject, 1);
    }
}

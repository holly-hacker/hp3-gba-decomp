#include "types.h"
#include "battle.h"

// ApplyDamageToFighter's sibling for status ticks (poison) -- same
// HP-underflow/faint check and animation-state write, but no XP/gold
// reward payout: a status tick isn't a kill-credited attack.
void ApplyStatusDamageToFighter_candidate(s32 damage, s32 fighterIndex)
{
    // Strips ResolveEnemyAttack/ResolvePlayerAttack's "Critical hit!" sentinel.
    if ((u32)damage > 998)
        damage -= 999;

    g_pFightState->pFighters[fighterIndex].wHp -= damage;

    if (g_pFightState->pFighters[fighterIndex].wHp == 0
        || g_pFightState->pFighters[fighterIndex].wHp > g_pFightState->pFighters[fighterIndex].wHp_max)
    {
        if (g_pFightState->bFaintMessageCount_candidate == 0)
            ShowBattleMessage(AttackResult, (u16)fighterIndex, 2);

        g_pFightState->dwDefeatCheckPending_candidate = 1;
        g_pFightState->pFighters[fighterIndex].wHp = 0;
        g_pFightState->pFighters[fighterIndex].nFaintedFlag = -1;

        {
            u8 idx = fighterIndex;
            ClearPoisonedFighter_candidate(idx);
            ClearParalyzedFighter_candidate(idx);
        }

        SetFighterAttackAnimState_candidate(g_pFightState->pFighters[fighterIndex].pObject, 1);

        if (g_pFightState->bMenuScreen != 0 && g_pFightState->bMenuFighterIndex == fighterIndex)
        {
            g_pFightState->bMenuFighterIndex |= 0xff;
            g_pFightState->bMenuScreen = 0x80;
        }
    }

    g_aPartyMasterStats[g_pFightState->pFighters[fighterIndex].bFighterType].wHp =
        g_pFightState->pFighters[fighterIndex].wHp;

    if (g_pFightState->bActiveFighterIndex == fighterIndex)
        DrawFighterStatsUi_candidate(g_pFightState->pFighters[fighterIndex].bFighterType, 0);
}

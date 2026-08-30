#include "types.h"
#include "battle.h"
#include "mt19937.h"

#define ATTACKER (g_pFightState->pFighters[attackerIndex])
#define DEFENDER (g_pFightState->pFighters[defenderIndex])

// Handle monster attack damage calculation
s32 ResolveEnemyAttack(s32 attackerIndex, s32 defenderIndex)
{
    BattleFighter *pFighters;
    u8 accuracy;
    u16 hitRoll;
    u32 damage;
    u16 critRoll;

    pFighters = g_pFightState->pFighters;

    // Hidden lowers the attacker's effective accuracy by 25.
    if (pFighters[defenderIndex].bStatusFlags & Hidden)
        accuracy = pFighters[attackerIndex].bAccuracy - 25;
    else
        accuracy = pFighters[attackerIndex].bAccuracy;

    hitRoll = Mt19937RandMax(99);
    if (hitRoll < accuracy)
    {
        damage = Mt19937RandRange(ATTACKER.wDamageRollMin, ATTACKER.wDamageRollMax);
        damage = (damage * DEFENDER.bDefenseFactorPercent) / 100;

        // AttackWeakened (Spongify) and DefenseBoost (Be More Careful) each halve damage, stacking to a quarter.
        if (ATTACKER.bStatusFlags & AttackWeakened)
        {
            // Hermione's "Be More Careful"
            if ((DEFENDER.bStatusFlags & DefenseBoost))
            {
                damage /= 4;
            }
            else
            {
                damage /= 2;
                goto halveCheck;
            }
        }
        else
        {
halveCheck:
            // Hermione's "Be More Careful"
            if (DEFENDER.bStatusFlags & DefenseBoost)
                damage /= 2;
        }
        damage += 1;
    }
    else
    {
        damage = 0;
    }

    // Roll for crit if not a miss and target is not hidden
    if (damage != 0 && !(DEFENDER.bStatusFlags & Hidden))
    {
        critRoll = Mt19937RandMax(100);
        if (critRoll > 100 - ATTACKER.bCritChance)
        {
            damage *= 2;
            damage += 999;
        }
    }

    return damage;
}

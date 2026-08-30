#include "types.h"
#include "battle.h"
#include "mt19937.h"

#define ATTACKER (g_pFightState->pFighters[attackerIndex])
#define DEFENDER (g_pFightState->pFighters[defenderIndex])

// Handle monster attack damage calculation
s32 ResolveEnemyAttack(s32 attackerIndex, s32 defenderIndex)
{
    u8 accuracy;
    u16 hitRoll;
    u32 damage;
    u16 critRoll;

    // Fumos lowers the attacker's effective accuracy by 25.
    if (DEFENDER.bStatusFlags & Hidden)
        accuracy = ATTACKER.bAccuracy - 25;
    else
        accuracy = ATTACKER.bAccuracy;

    // Roll for accuracy
    hitRoll = Mt19937RandMax(99);
    if (hitRoll < accuracy)
    {
        damage = Mt19937RandRange(ATTACKER.wDamageRollMin, ATTACKER.wDamageRollMax);
        damage = (damage * DEFENDER.bDefenseFactorPercent) / 100;

        // Spongify or Hermione's "Be More Careful"
        if ((ATTACKER.bStatusFlags & AttackWeakened) && (DEFENDER.bStatusFlags & DefenseBoost))
        {
            damage /= 4;
        }
        else
        {
            // Spongify
            if (ATTACKER.bStatusFlags & AttackWeakened)
                damage /= 2;

            // "Be More Careful"
            if (DEFENDER.bStatusFlags & DefenseBoost)
                damage /= 2;
        }

        damage += 1;
    }
    else
    {
        damage = 0;
    }

    // Roll for crit if not a miss and target is not under Fumos
    if (damage != 0 && !(DEFENDER.bStatusFlags & Hidden))
    {
        critRoll = Mt19937RandMax(100);
        if (critRoll > 100 - ATTACKER.bCritChance)
        {
            damage *= 2;

            // Sentinel/marker value
            damage += 999;
        }
    }

    return damage;
}

#include "types.h"
#include "battle.h"
#include "mt19937.h"
#include "constants/spells.h"

#define ATTACKER (g_pFightState->pFighters[attackerIndex])
#define TARGET (g_pFightState->pFighters[targetIndex])

// Harry/Hermione/Ron spell damage calculation. Buckbeak has its own handling elsewhere.
s32 ResolvePlayerAttack(s32 attackerIndex, s32 targetIndex)
{
    u32 power;
    u32 effectiveness;
    s32 crit = 0;
    u8 critChance;
    u8 attackerLevel;
    u16 roll;

    // check if the attack hits or misses. If it missed twice in a row, the next roll is guaranteed to succeed.
    if ((g_bSpellMissStreak >= 2) || ((u16)Mt19937RandMax(100) < ATTACKER.bAccuracy))
    {
        g_bSpellMissStreak = 0;

        // base power is expressed as `base_power + (scale * player.level) / 9`
        power = g_awSpellPowerBase[ATTACKER.bSpellId][ATTACKER.bSpellLevel];
        power += (g_awSpellPowerScale[ATTACKER.bSpellId][ATTACKER.bSpellLevel] * ATTACKER.bLevel) / 9;

        // boost Hermione's attack by 6.25%, lower Ron's attack by 6.25%
        switch (ATTACKER.bFighterType)
        {
        case Ron:      power = (power * 15) / 16; break;
        case Hermione: power = (power * 17) / 16; break;
        // explicit case is required for matching compiler output
        case Harry:
        default:       break;
        }

        // ensure at least 1 attack to prevent hit from being recognized as miss
        // This should be unreachable, as the lowest output is Lv1 Ron's Flipendo Uno, whose damage
        // is `(10 + (4*1)/9) * 15 / 16 = (10 + 0) * 15 / 16 = 150/16 = 9`
        if (power == 0)
            power = 1;

        // Hermione's "Proper Wand Technique" boosts attack by 33%
        if (ATTACKER.bStatusFlags & SpellPowerBoost)
            power = (power * 4) / 3;
    }
    else
    {
        // bump spell miss streak, set power to 0 for early exit
        g_bSpellMissStreak++;
        power = 0;
    }

    // goto to prevent big if block, `return 0` causes non-matching compilation output
    if (power == 0)
        goto done;

    // Crit chance is 50% of the player's level, or 75% if using PWT, capped to 12.
    // You hit max crit chance at lv24, or lv16 with PWT.
    attackerLevel = ATTACKER.bLevel;
    if (attackerLevel >= 2)
    {
        critChance = attackerLevel >> 1;

        // Hermione's "Proper Wand Technique" boosts crit chance by 25% of player level
        if (ATTACKER.bStatusFlags & SpellPowerBoost)
            critChance += (attackerLevel >> 1) >> 1;

        if (critChance > 12)
            critChance = 12;
    }
    else
    {
        // never crit at level 1. This branch is useless, since 1 >> 1 is 0 anyway.
        critChance = 0;
    }

    // get spell effectiveness on monster, 0-100
    switch (ATTACKER.bSpellId)
    {
    case Flipendo:          effectiveness = TARGET.bEffectivenessFlipendo;          break;
    case Incendio:          effectiveness = TARGET.bEffectivenessIncendio;          break;
    case Verdimillious:     effectiveness = TARGET.bEffectivenessVerdimillious;     break;
    case WingardiumLeviosa: effectiveness = TARGET.bEffectivenessWingardiumLeviosa; break;
    case Glacius:           effectiveness = TARGET.bEffectivenessGlacius;           break;
    case Diffindo:          effectiveness = TARGET.bEffectivenessDiffindo;          break;
    default:
        return 0;
    }

    roll = Mt19937RandMax(100);

    // 2% base crit chance, boosted by up to 12% because of level or Hermione's PWT.
    if (roll > (97 - critChance))
    {
        crit = 1;
        power *= 2;
    }

    // multiply power by effectiveness percentage
    power = (power * effectiveness) / 100;

    // ensure there's no zero power hits
    power += 1;

    // +1000 is a "Critical hit!" sentinel, not literal damage
    if (crit)
        power += 1000;

done:
    return power;
}

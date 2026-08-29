#include "types.h"
#include "battle.h"
#include "mt19937.h"
#include "constants/spells.h"

extern const u16 g_awSpellPowerBase[SPELL_COUNT][SPELL_LEVELS];
extern const u16 g_awSpellPowerScale[SPELL_COUNT][SPELL_LEVELS];

#define ATTACKER (g_pFightState->pFighters[attackerIndex])
#define TARGET (g_pFightState->pFighters[targetIndex])

// Harry/Hermione/Ron spell-cast damage formula. See docs/memory-map/battle.md.
// Not called for Buckbeak -- ExecutePlayerAttackSequence hardcodes his damage
// separately. Matches the ROM byte for byte.
s32 ResolvePlayerAttack(s32 attackerIndex, s32 targetIndex)
{
    // u32: the Hermione/Ron division by 16 below needs unsigned codegen.
    u32 power;
    u8 critChance;
    u32 effectiveness;
    s32 crit = 0;
    u8 attackerLevel;
    u16 roll;

    if ((g_bSpellMissStreak >= 2) ||
        ((u16)Mt19937RandMax(100) < ATTACKER.bAccuracy))
    {
        g_bSpellMissStreak = 0;
        // Re-derives ATTACKER.x each use and keeps the lookup its own
        // statement -- both needed for matching codegen.
        power = g_awSpellPowerBase[ATTACKER.bSpellId][ATTACKER.bSpellLevel];
        power += (g_awSpellPowerScale[ATTACKER.bSpellId][ATTACKER.bSpellLevel] * ATTACKER.bLevel) / 9;

        switch (ATTACKER.bFighterType)
        {
        case Ron:      power = (power * 15) / 16; break;
        case Hermione: power = (power * 17) / 16; break;
        // Harry needs an explicit case; Buckbeak default-cases fine.
        case Harry:
        default:       break;
        }

        if (power == 0)
            power = 1;

        // also boosts crit chance below
        if (ATTACKER.bStatusFlags & SpellPowerBoost)
        {
            power = (power * 4) / 3;
        }
    }
    else
    {
        g_bSpellMissStreak++;
        power = 0;
    }

    // goto, not a wrapping `if` block -- nesting shifts agbcc's codegen.
    if (power == 0)
        goto done;

    attackerLevel = ATTACKER.bLevel;

    if (attackerLevel >= 2)
    {
        critChance = attackerLevel >> 1;

        if (ATTACKER.bStatusFlags & SpellPowerBoost)
            critChance += (attackerLevel >> 1) >> 1;

        if (critChance > 12)
            critChance = 12;
    }
    else
    {
        critChance = 0;
    }

    // status-only spells (Informus/PetrificusTotalus/Fumos/Spongify) return 0.
    // Case order follows struct field offset, not spell id -- needed for codegen.
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

    if (roll > (0x61 - critChance))
    {
        crit = 1;
        power <<= 1;
    }

    power = (power * effectiveness) / 100;
    power = power + 1;

    // +1000 is a "Critical hit!" sentinel, not literal damage
    if (crit)
        power += 1000;

done:
    return power;
}

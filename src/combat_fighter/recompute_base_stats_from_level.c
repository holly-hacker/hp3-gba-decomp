#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// Resets what ApplyEquipmentStatModifiers adjusts: agility to the current
// level's value and both defense percentages to 100.
void RecomputeBaseStatsFromLevel(u32 character)
{
    const CharacterLevelEntry *table;

    switch (character)
    {
    case Harry:
    default:
        table = g_pHarryLevelTable;
        break;
    case Hermione:
        table = g_pHermioneLevelTable;
        break;
    case Ron:
        table = g_pRonLevelTable;
        break;
    }

    g_aPartyMasterStats[character].bDefenseFactorPercent = 100;
    g_aPartyMasterStats[character].bAgility = table[g_aPartyMasterStats[character].stats.bLevel].bAgility;
    g_aPartyMasterStats[character].bMagicDefensePercent = 100;
}

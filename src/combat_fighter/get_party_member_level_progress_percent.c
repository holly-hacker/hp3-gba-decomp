#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// How far a party member is through their current level, 0-100. No callers.
u32 GetPartyMemberLevelProgressPercent(u32 slot)
{
    const CharacterLevelEntry *table;

    switch (slot)
    {
    default:
        return 0;
    case Harry:
        table = g_pHarryLevelTable;
        break;
    case Hermione:
        table = g_pHermioneLevelTable;
        break;
    case Ron:
        table = g_pRonLevelTable;
        break;
    }

    return (u32)((table[g_aPartyMasterStats[slot].stats.bLevel].wXpDeltaForLevel
                  - (s16)g_aPartyMasterStats[slot].stats.wRewardXp) * 100)
           / table[g_aPartyMasterStats[slot].stats.bLevel].wXpDeltaForLevel;
}

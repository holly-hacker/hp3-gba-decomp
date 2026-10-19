#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// The XP the party member needed to reach their current level. No callers.
u32 GetPartyMemberLastLevelUpXp(u32 character)
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

    return table[g_aPartyMasterStats[character].stats.bLevel - 1].wXpDeltaForLevel;
}

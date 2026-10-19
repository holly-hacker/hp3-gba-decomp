#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// The XP a party member has earned in total: the XP of every completed level
// plus the progress into the current one (its XP minus what is still needed).
s32 GetPartyMemberTotalXp(u32 slot)
{
    const CharacterLevelEntry *table;
    u32 xpForLevel;
    u32 i;
    s32 sum;

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

    xpForLevel = table[g_aPartyMasterStats[slot].stats.bLevel].wXpDeltaForLevel;
    if (g_aPartyMasterStats[slot].stats.bLevel == 1)
        return xpForLevel - (s16)g_aPartyMasterStats[slot].stats.wRewardXp + table[0].wXpDeltaForLevel;

    if (g_aPartyMasterStats[slot].stats.bLevel > 1)
    {
        sum = 0;
        for (i = 0; i < g_aPartyMasterStats[slot].stats.bLevel; i++)
            sum += table[i].wXpDeltaForLevel;
        return xpForLevel - (s16)g_aPartyMasterStats[slot].stats.wRewardXp + sum;
    }

    return xpForLevel - (s16)g_aPartyMasterStats[slot].stats.wRewardXp;
}

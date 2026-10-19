#include "types.h"
#include "combat_fighter.h"
#include "combat_end.h"
#include "combat.h"

#define MAX_LEVEL 99

// Counts xp off the party member's experience-to-next-level (wRewardXp), levelling up each time it
// reaches 0 and carrying the excess into the next level. Returns the number of level-ups.
u32 GrantPartyMemberXp(u32 fighterType, s32 xp)
{
    u32 levelUps;
    s32 remaining;

    levelUps = 0;
    remaining = xp;
    while (g_aPartyMasterStats[fighterType].stats.bLevel != MAX_LEVEL)
    {
        g_aPartyMasterStats[fighterType].stats.wRewardXp -= remaining;
        if ((s16)g_aPartyMasterStats[fighterType].stats.wRewardXp > 0)
            break;

        remaining = -(s16)g_aPartyMasterStats[fighterType].stats.wRewardXp;
        LevelUpPartyMember_candidate(fighterType);
        levelUps++;
    }

    return levelUps;
}

#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// Rederives every party member's level stats and fully restores HP and MP.
void ResetPartyHpMpAndStats(void)
{
    u32 i;

    for (i = 0; i < 3; i++)
    {
        InitPartyStatForCurrentLevel(i);
        g_aPartyMasterStats[i].stats.wHp = g_aPartyMasterStats[i].wHp_max;
        g_aPartyMasterStats[i].stats.wMp = g_aPartyMasterStats[i].wMp_max;
    }
}

#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

s32 GetPartyMemberXpToNextLevel(u32 slot)
{
    return (s16)g_aPartyMasterStats[slot].stats.wRewardXp;
}

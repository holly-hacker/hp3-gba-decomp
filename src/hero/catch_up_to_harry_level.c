#include "types.h"
#include "combat.h"
#include "combat_fighter.h"
#include "random.h"
#include "overworld/room_script.h"

// Levels a recruited Hermione or Ron up to Harry's level, then takes away 0-10 experience.
// It does nothing if they are within 2 levels of Harry, unless Harry is level 4 or lower.
// While Harry is level 5-98, the level they reach is randomly up to 2 above or below his.
void CatchUpToHarryLevel(u8 characterId)
{
    u8 slot;
    u8 targetLevel;
    u8 level;

    slot = GetCharacterFighterType(characterId);
    if (slot == Harry || slot == Buckbeak)
        return;
    if (g_aPartyMasterStats[slot].stats.bLevel >= g_aPartyMasterStats[Harry].stats.bLevel)
        return;
    if (g_aPartyMasterStats[Harry].stats.bLevel - g_aPartyMasterStats[slot].stats.bLevel <= 2
        && g_aPartyMasterStats[Harry].stats.bLevel > 4)
        return;

    if (g_aPartyMasterStats[Harry].stats.bLevel <= 4)
        targetLevel = g_aPartyMasterStats[Harry].stats.bLevel;
    else if (g_aPartyMasterStats[Harry].stats.bLevel > 98)
        targetLevel = g_aPartyMasterStats[Harry].stats.bLevel;
    else
        targetLevel = Mt19937RandSigned(2) + g_aPartyMasterStats[Harry].stats.bLevel;

    for (level = g_aPartyMasterStats[slot].stats.bLevel; level < targetLevel; level++)
        LevelUpPartyMember(slot);

    g_aPartyMasterStats[slot].stats.wRewardXp -= Mt19937RandMax(10);
}

#include "types.h"
#include "combat_fighter.h"
#include "items.h"
#include "combat.h"

#define MAX_LEVEL 99

#define FIGHTER g_aPartyMasterStats[fighterType]
#define NEW_LEVEL table[FIGHTER.stats.bLevel]

// Advances a party member one level, up to MAX_LEVEL: loads the new level's
// stats and XP to the next level, fully restores HP and MP, and reapplies
// equipment modifiers.
void LevelUpPartyMember(u32 fighterType)
{
    const CharacterLevelEntry *table;

    switch (fighterType)
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

    if (FIGHTER.stats.bLevel < MAX_LEVEL)
    {
        FIGHTER.stats.bLevel++;
        FIGHTER.stats.wRewardXp = NEW_LEVEL.wXpDeltaForLevel;
        FIGHTER.wHp_max = NEW_LEVEL.wHp_max;
        FIGHTER.wMp_max = NEW_LEVEL.wMp_max;
        FIGHTER.bAgility = NEW_LEVEL.bAgility;
        FIGHTER.bAccuracy = NEW_LEVEL.bAccuracy;
        FIGHTER.bDefenseFactorPercent = NEW_LEVEL.bDefenseFactorPercent;
        FIGHTER.bMagicDefensePercent = NEW_LEVEL.bMagicDefensePercent;
        FIGHTER.stats.wHp = FIGHTER.wHp_max;
        FIGHTER.stats.wMp = FIGHTER.wMp_max;
        ApplyEquipmentStatModifiers();
    }
}

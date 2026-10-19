#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// Sets a party member's saved stats to the start of the given level: full HP
// and MP, that level's XP to the next one, and every spell at cast level 1.
// Hermione starts with four known spells, the others with three.
void ResetCharacterToLevel(u32 character, u32 level)
{
    BattleFighter *fighter;
    const CharacterLevelEntry *row;
    u32 i;

    fighter = &g_aPartyMasterStats[character];
    row = &g_apCharacterLevelTables[character][level];
    fighter->stats.wHp = row->wHp_max;
    fighter->stats.wMp = row->wMp_max;
    fighter->stats.wRewardXp = row->wXpDeltaForLevel;
    fighter->stats.bLevel = level;
    if (character == Hermione)
        fighter->stats.bKnownSpellCount = 4;
    else
        fighter->stats.bKnownSpellCount = 3;
    for (i = 0; i < 10; i++)
        fighter->stats.aSpellCastLevel[i] = 1;

    InitPartyStatForCurrentLevel(character);
}

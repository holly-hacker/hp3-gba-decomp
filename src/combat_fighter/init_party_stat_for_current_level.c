#include "types.h"
#include "combat_fighter.h"
#include "combat.h"

// Derives a party member's level-dependent battle stats from their saved
// level, and clears their status and fainted state.
void InitPartyStatForCurrentLevel(u32 index)
{
    BattleFighter *fighter;
    const CharacterLevelEntry *row;

    fighter = &g_aPartyMasterStats[index];
    row = &g_apCharacterLevelTables[index][fighter->stats.bLevel];
    fighter->wHp_max = row->wHp_max;
    fighter->wMp_max = row->wMp_max;
    fighter->bAgility = row->bAgility;
    fighter->bAccuracy = row->bAccuracy;
    fighter->bDefenseFactorPercent = 100;
    fighter->bMagicDefensePercent = 100;
    fighter->bStatusFlags = StatusNone;
    fighter->nTurnKey = 0;
}

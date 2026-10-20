#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "constants/spells.h"

void LearnAllSpells(u32 fighterType, SavedFighterStats *stats)
{
    u32 i;

    if (fighterType == Hermione) {
        stats->bKnownSpellCount = 7;
        g_aPartyMasterStats[fighterType].stats.bKnownSpellCount = 7;
    } else {
        stats->bKnownSpellCount = 6;
        g_aPartyMasterStats[fighterType].stats.bKnownSpellCount = 6;
    }

    for (i = 0; i < SPELL_COUNT; i++) {
        stats->aSpellCastLevel[i] = g_abSpellMaxLevel[i];
        g_aPartyMasterStats[fighterType].stats.aSpellCastLevel[i] = stats->aSpellCastLevel[i];
    }
}

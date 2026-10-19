#include "types.h"
#include "combat.h"
#include "combat_core.h"
#include "combat_dialog.h"
#include "save.h"

// Credits a cast to the caster's spell usage and its party master record. A cast at
// spellLevel (0 = Uno) is worth spellLevel + 1 points; reaching the current cast level's
// threshold levels the spell up. Buckbeak and capped spells gain nothing.
void TrackSpellFamiliarity(u32 fighterType, u32 spellId, s32 spellLevel, SavedFighterStats *pStats)
{
    if (pStats->aSpellCastLevel[spellId] < g_abSpellMaxLevel[spellId] && fighterType != Buckbeak) {
        spellLevel++;
        pStats->aSpellUsageProgress[spellId] += spellLevel;
        g_aPartyMasterStats[fighterType].stats.aSpellUsageProgress[spellId] += spellLevel;

        if (pStats->aSpellUsageProgress[spellId]
            >= g_abSpellLevelUpThreshold[pStats->aSpellCastLevel[spellId] - 1]) {
            ShowBattleMessage(SpellLevelUp, 0, 0);
            pStats->aSpellCastLevel[spellId]++;
            pStats->aSpellUsageProgress[spellId] = 0;
            g_aPartyMasterStats[fighterType].stats.aSpellCastLevel[spellId]++;
            g_aPartyMasterStats[fighterType].stats.aSpellUsageProgress[spellId] = 0;
        }
    }
}

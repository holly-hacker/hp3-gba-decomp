#include "types.h"
#include "combat_fighter.h"
#include "mem.h"
#include "save.h"
#include "items.h"
#include "combat.h"

// Reads the three party members' saved fields and then derives their
// level-dependent stats.
void DeserializePartyStats(void)
{
    u32 i;
    SavedFighterStats *pStats;

    for (i = 0; i < 3; i++)
    {
        pStats = (SavedFighterStats *)&g_aPartyMasterStats[i].wHp;
        memset(pStats, 0, sizeof(SavedFighterStats));
        UnpackBytesFromSaveStream(&pStats->wHp, 2);
        UnpackBytesFromSaveStream(&pStats->wMp, 2);
        UnpackBytesFromSaveStream(&pStats->wRewardXp, 2);
        UnpackBytesFromSaveStream(&pStats->bLevel, 1);
        UnpackBytesFromSaveStream(&pStats->bKnownSpellCount, 1);
        UnpackBytesFromSaveStream(pStats->aSpellCastLevel, 10);
        UnpackBytesFromSaveStream(pStats->aSpellUsageProgress, 10);
        InitPartyStatForCurrentLevel(i);
    }
    ApplyEquipmentStatModifiers();
}

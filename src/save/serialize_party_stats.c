#include "types.h"
#include "battle/battle.h"
#include "game/save.h"

// Writes the three party members' saved fields.
void SerializePartyStats(void)
{
    u32 i;
    SavedFighterStats *pStats;

    for (i = 0; i < 3; i++)
    {
        pStats = (SavedFighterStats *)&g_aPartyMasterStats[i].wHp;
        PackBytesToSaveStream(&pStats->wHp, 2);
        PackBytesToSaveStream(&pStats->wMp, 2);
        PackBytesToSaveStream(&pStats->wRewardXp, 2);
        PackBytesToSaveStream(&pStats->bLevel, 1);
        PackBytesToSaveStream(&pStats->bKnownSpellCount, 1);
        PackBytesToSaveStream(pStats->aSpellCastLevel, 10);
        PackBytesToSaveStream(pStats->aSpellUsageProgress, 10);
    }
}

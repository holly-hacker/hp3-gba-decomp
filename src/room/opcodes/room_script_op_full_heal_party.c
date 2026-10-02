#include "types.h"
#include "battle/battle.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

void RoomScriptOpFullHealParty(RoomScriptRecord *pRecord)
{
    u8 i;

    g_abQuestEventState[QUEST_SCRATCH_RESULT] = 0;
    for (i = 0; i < 3; i++)
    {
        if (g_aPartyMasterStats[i].wHp != g_aPartyMasterStats[i].wHp_max ||
            g_aPartyMasterStats[i].wMp != g_aPartyMasterStats[i].wMp_max)
            g_abQuestEventState[QUEST_SCRATCH_RESULT] = 1;

        g_aPartyMasterStats[i].wHp = g_aPartyMasterStats[i].wHp_max;
        g_aPartyMasterStats[i].wMp = g_aPartyMasterStats[i].wMp_max;
    }
}

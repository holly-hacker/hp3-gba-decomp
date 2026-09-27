#include "types.h"
#include "battle.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpFullHealParty(RoomScriptRecord *pRecord)
{
    u8 i;

    g_abQuestEventState[0xff] = 0;
    for (i = 0; i < 3; i++)
    {
        if (g_aPartyMasterStats[i].wHp != g_aPartyMasterStats[i].wHp_max ||
            g_aPartyMasterStats[i].wMp != g_aPartyMasterStats[i].wMp_max)
            g_abQuestEventState[0xff] = 1;

        g_aPartyMasterStats[i].wHp = g_aPartyMasterStats[i].wHp_max;
        g_aPartyMasterStats[i].wMp = g_aPartyMasterStats[i].wMp_max;
    }
}

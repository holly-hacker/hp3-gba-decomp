#include "types.h"
#include "overworld.h"
#include "room_script.h"

void RoomScriptOpRecruitPartyFollower(RoomScriptRecord *pRecord)
{
    SyncFollowerLevelToLeader_candidate(pRecord->operand.ab[0]);
    if (g_pFollowerObject0 == NULL)
    {
        sub_08024980(pRecord->operand.ab[0]);
        g_bPartyCharId1 = g_pFollowerObject0->wCharacterId_candidate;
    }
    else
    {
        sub_080249A4(pRecord->operand.ab[0]);
        g_bPartyCharId2 = g_pFollowerObject1->wCharacterId_candidate;
    }
}

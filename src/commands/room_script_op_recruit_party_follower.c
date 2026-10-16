#include "types.h"
#include "commands.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct RecruitPartyFollowerRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} RecruitPartyFollowerRecord;

void RoomScriptOpRecruitPartyFollower(RecruitPartyFollowerRecord *pRecord)
{
    SyncFollowerLevelToLeader_candidate(pRecord->bCharacterId);
    if (g_pFollowerActor0 == NULL)
    {
        sub_08024980(pRecord->bCharacterId);
        g_bPartyCharId1 = g_pFollowerActor0->wCharacterId_candidate;
    }
    else
    {
        sub_080249A4(pRecord->bCharacterId);
        g_bPartyCharId2 = g_pFollowerActor1->wCharacterId_candidate;
    }
}

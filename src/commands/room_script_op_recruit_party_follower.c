#include "types.h"
#include "commands.h"
#include "overworld/room_script.h"
#include "hero.h"

typedef struct RecruitPartyFollowerRecord {
    u32 dwOpcode;
    u8 bCharacterId;
} RecruitPartyFollowerRecord;

void RoomScriptOpRecruitPartyFollower(RecruitPartyFollowerRecord *pRecord)
{
    CatchUpToHarryLevel(pRecord->bCharacterId);
    if (g_pFollowerActor0 == NULL)
    {
        SpawnFollowerActor0(pRecord->bCharacterId);
        g_bPartyCharId1 = g_pFollowerActor0->wCharacterId_candidate;
    }
    else
    {
        SpawnFollowerActor1(pRecord->bCharacterId);
        g_bPartyCharId2 = g_pFollowerActor1->wCharacterId_candidate;
    }
}

#include "types.h"
#include "overworld/room_script.h"

typedef struct GrantPartyLevelUpsRecord {
    u32 dwOpcode;
    u8 bLevelCount;
} GrantPartyLevelUpsRecord;

void RoomScriptOpGrantPartyLevelUps(GrantPartyLevelUpsRecord *pRecord)
{
    s32 i;

    for (i = 0; i < pRecord->bLevelCount; i++)
    {
        LevelUpPartyMember_candidate(0);
        LevelUpPartyMember_candidate(1);
        LevelUpPartyMember_candidate(2);
    }
}

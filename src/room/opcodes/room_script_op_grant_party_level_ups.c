#include "types.h"
#include "room_script.h"

void RoomScriptOpGrantPartyLevelUps(RoomScriptRecord *pRecord)
{
    s32 i;

    for (i = 0; i < pRecord->operand.ab[0]; i++)
    {
        LevelUpPartyMember_candidate(0);
        LevelUpPartyMember_candidate(1);
        LevelUpPartyMember_candidate(2);
    }
}

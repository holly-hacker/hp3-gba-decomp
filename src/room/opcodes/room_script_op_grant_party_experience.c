#include "types.h"
#include "room_script.h"

void RoomScriptOpGrantPartyExperience(RoomScriptRecord *pRecord)
{
    GrantPartyExperience_candidate(pRecord->operand.aw[0]);
}

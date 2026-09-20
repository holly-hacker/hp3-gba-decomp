#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpAddQuestState(RoomScriptRecord *pRecord)
{
    g_abQuestEventState[pRecord->operand.ab[1]] += pRecord->operand.ab[0];
}

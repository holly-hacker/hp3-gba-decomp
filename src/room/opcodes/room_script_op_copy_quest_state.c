#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpCopyQuestState(RoomScriptRecord *pRecord)
{
    g_abQuestEventState[pRecord->operand.ab[1]] = g_abQuestEventState[pRecord->operand.ab[0]];
}

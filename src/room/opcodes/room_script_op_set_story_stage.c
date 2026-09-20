#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpSetStoryStage(RoomScriptRecord *pRecord)
{
    g_abQuestEventState[0] = pRecord->operand.ab[0];
}

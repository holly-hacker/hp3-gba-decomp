#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpGotoIfStoryStageCompare(RoomScriptRecord *pRecord)
{
    CompareAndBranchRoomScript_candidate(g_abQuestEventState[0], pRecord->operand.ab[0], pRecord->operand.ab[1],
                                         pRecord->operand.ab[2], pRecord->operand.ab[3], pRecord->operand.ab[4],
                                         pRecord->operand.ab[5]);
}

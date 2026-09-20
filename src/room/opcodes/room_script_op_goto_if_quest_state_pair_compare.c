#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpGotoIfQuestStatePairCompare(RoomScriptRecord *pRecord)
{
    CompareAndBranchRoomScript_candidate(g_abQuestEventState[pRecord->operand.ab[0]], pRecord->operand.ab[1],
                                         g_abQuestEventState[pRecord->operand.ab[2]], pRecord->operand.ab[3],
                                         pRecord->operand.ab[4], pRecord->operand.ab[5], pRecord->operand.ab[6]);
}

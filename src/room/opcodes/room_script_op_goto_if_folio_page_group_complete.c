#include "types.h"
#include "room_script.h"
#include "room_script_branch.h"

void RoomScriptOpGotoIfFolioPageGroupComplete(RoomScriptRecord *pRecord)
{
    CompareAndBranchRoomScript(IsFolioPageGroupUnlocked_candidate(pRecord->operand.ab[0]), RoomScriptCompareEqual, 1,
                               pRecord->operand.ab[2], pRecord->operand.ab[4], pRecord->operand.ab[1],
                               pRecord->operand.ab[3]);
}

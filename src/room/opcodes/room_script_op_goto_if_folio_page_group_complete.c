#include "types.h"
#include "overworld/room_script.h"
#include "overworld/room_script_branch.h"

typedef struct GotoIfFolioPageGroupCompleteRecord {
    u32 dwOpcode;
    u8 bPageGroupId;
    u8 bTrueRow;
    u8 bTrueChain;
    u8 bFalseRow;
    u8 bFalseChain;
} GotoIfFolioPageGroupCompleteRecord;

void RoomScriptOpGotoIfFolioPageGroupComplete(GotoIfFolioPageGroupCompleteRecord *pRecord)
{
    CompareAndBranchRoomScript(IsFolioPageGroupUnlocked_candidate(pRecord->bPageGroupId), RoomScriptCompareEqual, 1,
                               pRecord->bTrueChain, pRecord->bFalseChain, pRecord->bTrueRow, pRecord->bFalseRow);
}

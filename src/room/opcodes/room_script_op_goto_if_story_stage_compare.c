#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct GotoIfStoryStageCompareRecord {
    u32 dwOpcode;
    u8 bCmpOp;
    u8 bValue;
    u8 bTrueChain;
    u8 bFalseChain;
    u8 bTrueRow;
    u8 bFalseRow;
} GotoIfStoryStageCompareRecord;

void RoomScriptOpGotoIfStoryStageCompare(GotoIfStoryStageCompareRecord *pRecord)
{
    CompareAndBranchRoomScript(g_abQuestEventState[0], pRecord->bCmpOp, pRecord->bValue, pRecord->bTrueChain,
                               pRecord->bFalseChain, pRecord->bTrueRow, pRecord->bFalseRow);
}

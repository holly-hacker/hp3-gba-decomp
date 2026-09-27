#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct GotoIfQuestStateCompareRecord {
    u32 dwOpcode;
    u8 bIndex;
    u8 bCmpOp;
    u8 bValue;
    u8 bTrueChain;
    u8 bFalseChain;
    u8 bTrueRow;
    u8 bFalseRow;
} GotoIfQuestStateCompareRecord;

void RoomScriptOpGotoIfQuestStateCompare(GotoIfQuestStateCompareRecord *pRecord)
{
    CompareAndBranchRoomScript(g_abQuestEventState[pRecord->bIndex], pRecord->bCmpOp, pRecord->bValue,
                               pRecord->bTrueChain, pRecord->bFalseChain, pRecord->bTrueRow, pRecord->bFalseRow);
}

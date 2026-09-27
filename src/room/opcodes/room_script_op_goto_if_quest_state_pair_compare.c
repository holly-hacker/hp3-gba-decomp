#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct GotoIfQuestStatePairCompareRecord {
    u32 dwOpcode;
    u8 bIndexA;
    u8 bCmpOp;
    u8 bIndexB;
    u8 bTrueChain;
    u8 bFalseChain;
    u8 bTrueRow;
    u8 bFalseRow;
} GotoIfQuestStatePairCompareRecord;

void RoomScriptOpGotoIfQuestStatePairCompare(GotoIfQuestStatePairCompareRecord *pRecord)
{
    CompareAndBranchRoomScript(g_abQuestEventState[pRecord->bIndexA], pRecord->bCmpOp,
                               g_abQuestEventState[pRecord->bIndexB], pRecord->bTrueChain, pRecord->bFalseChain,
                               pRecord->bTrueRow, pRecord->bFalseRow);
}

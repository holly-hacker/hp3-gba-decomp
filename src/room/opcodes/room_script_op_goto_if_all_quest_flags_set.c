#include "types.h"
#include "room.h"
#include "room_script.h"
#include "room_script_branch.h"

typedef struct GotoIfAllQuestFlagsSetRecord {
    u32 dwOpcode;
    u8 bTrueChain;
    u8 bFalseChain;
    u8 bTrueRow;
    u8 bFalseRow;
} GotoIfAllQuestFlagsSetRecord;

// Branches on whether quest event state bytes 0x14-0x18 are all nonzero.
void RoomScriptOpGotoIfAllQuestFlagsSet(GotoIfAllQuestFlagsSetRecord *pRecord)
{
    u32 allSet = 1;
    u32 i;

    for (i = 0x14; i <= 0x18; i++)
    {
        if (g_abQuestEventState[i] == 0)
            allSet = 0;
    }

    CompareAndBranchRoomScript(allSet, RoomScriptCompareEqual, 1, pRecord->bTrueChain, pRecord->bFalseChain,
                               pRecord->bTrueRow, pRecord->bFalseRow);
}

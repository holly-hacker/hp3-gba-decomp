#include "types.h"
#include "room.h"
#include "room_script.h"
#include "room_script_branch.h"

// Branches on whether quest event state bytes 0x14-0x18 are all nonzero.
void RoomScriptOpGotoIfAllQuestFlagsSet(RoomScriptRecord *pRecord)
{
    u32 allSet = 1;
    u32 i;

    for (i = 0x14; i <= 0x18; i++)
    {
        if (g_abQuestEventState[i] == 0)
            allSet = 0;
    }

    CompareAndBranchRoomScript(allSet, RoomScriptCompareEqual, 1, pRecord->operand.ab[0], pRecord->operand.ab[1],
                               pRecord->operand.ab[2], pRecord->operand.ab[3]);
}

#include "types.h"
#include "overworld/room_script.h"

typedef struct ArmChainYieldRecord {
    u32 dwOpcode;
    u8 bArm;
} ArmChainYieldRecord;

// Only the following opcode decides whether the walk yields (see the run state in room_script.h):
// handlers that bump 1 -> 2 do. Scripts write ArmChainYield 1 before such an opcode and 0 after.
void RoomScriptOpArmChainYield(ArmChainYieldRecord *pRecord)
{
    if (pRecord->bArm != 0)
        g_dwRoomScriptRunState = 1;
    else
        g_dwRoomScriptRunState = 0;
}

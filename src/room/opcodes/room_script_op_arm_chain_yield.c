#include "types.h"
#include "room_script.h"

typedef struct ArmChainYieldRecord {
    u32 dwOpcode;
    u8 bArm;
} ArmChainYieldRecord;

void RoomScriptOpArmChainYield(ArmChainYieldRecord *pRecord)
{
    if (pRecord->bArm != 0)
        g_dwRoomScriptRunState = 1;
    else
        g_dwRoomScriptRunState = 0;
}

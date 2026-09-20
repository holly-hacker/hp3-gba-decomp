#include "types.h"
#include "room_script.h"

void RoomScriptOpArmChainYield(RoomScriptRecord *pRecord)
{
    if (pRecord->operand.ab[0] != 0)
        g_dwRoomScriptRunState = 1;
    else
        g_dwRoomScriptRunState = 0;
}

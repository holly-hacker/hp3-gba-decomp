#include "types.h"
#include "room_script.h"

void RoomScriptOpSetPendingChainFromExitParam(RoomScriptRecord *pRecord)
{
    u8 exit = g_abRoomScriptExitParams_candidate[0];

    if (exit != 0)
    {
        if (exit == 1)
            g_bRoomScriptPendingChain = pRecord->operand.ab[0];
    }
    else
        g_bRoomScriptPendingChain = pRecord->operand.ab[1];
}

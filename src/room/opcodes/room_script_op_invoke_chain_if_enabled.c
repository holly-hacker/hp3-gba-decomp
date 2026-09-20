#include "types.h"
#include "room_script.h"

void RoomScriptOpInvokeChainIfEnabled(RoomScriptRecord *pRecord)
{
    g_bRoomScriptPendingChain = pRecord->operand.ab[1];
    if (ShouldRunRoomScriptRow_candidate(pRecord->operand.ab[0]))
        RespawnRoomObjectsInRow_candidate(pRecord->operand.ab[0]);
}

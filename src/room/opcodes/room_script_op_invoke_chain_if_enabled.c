#include "types.h"
#include "room_script.h"

typedef struct InvokeChainIfEnabledRecord {
    u32 dwOpcode;
    u8 bRow;
    u8 bChain;
} InvokeChainIfEnabledRecord;

void RoomScriptOpInvokeChainIfEnabled(InvokeChainIfEnabledRecord *pRecord)
{
    g_bRoomScriptPendingChain = pRecord->bChain;
    if (ShouldRunRoomScriptRow_candidate(pRecord->bRow))
        RespawnRoomObjectsInRow_candidate(pRecord->bRow);
}

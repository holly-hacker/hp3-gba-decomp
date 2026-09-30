#include "types.h"
#include "overworld/room_script.h"

typedef struct InvokeChainIfEnabledRecord {
    u32 dwOpcode;
    u8 bRow;
    u8 bChain;
} InvokeChainIfEnabledRecord;

// Every script passes row 0, which ShouldRunRoomScriptRow_candidate rejects, so this acts as an
// unconditional goto to bChain.
void RoomScriptOpInvokeChainIfEnabled(InvokeChainIfEnabledRecord *pRecord)
{
    g_bRoomScriptPendingChain = pRecord->bChain;
    if (ShouldRunRoomScriptRow_candidate(pRecord->bRow))
        RespawnRoomObjectsInRow_candidate(pRecord->bRow);
}

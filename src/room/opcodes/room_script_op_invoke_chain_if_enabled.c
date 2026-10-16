#include "types.h"
#include "area.h"
#include "overworld/room_script.h"

typedef struct InvokeChainIfEnabledRecord {
    u32 dwOpcode;
    u8 bRow;
    u8 bChain;
} InvokeChainIfEnabledRecord;

// Every script passes row 0, which ShouldRunRoomIndex rejects, so this acts as an
// unconditional goto to bChain.
void RoomScriptOpInvokeChainIfEnabled(InvokeChainIfEnabledRecord *pRecord)
{
    g_bRoomScriptPendingChain = pRecord->bChain;
    if (ShouldRunRoomIndex(pRecord->bRow))
        SpawnMissingRoomGroupActors(pRecord->bRow);
}

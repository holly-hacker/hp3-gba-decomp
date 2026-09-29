#include "types.h"
#include "overworld/room_script.h"

typedef struct SetPendingChainFromExitParamRecord {
    u32 dwOpcode;
    u8 bChainIfExit1;
    u8 bChainIfExit0;
} SetPendingChainFromExitParamRecord;

void RoomScriptOpSetPendingChainFromExitParam(SetPendingChainFromExitParamRecord *pRecord)
{
    u8 exit = g_abRoomScriptExitParams_candidate[0];

    if (exit != 0)
    {
        if (exit == 1)
            g_bRoomScriptPendingChain = pRecord->bChainIfExit1;
    }
    else
        g_bRoomScriptPendingChain = pRecord->bChainIfExit0;
}

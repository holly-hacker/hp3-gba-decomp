#include "types.h"
#include "room_script.h"

typedef struct RespawnRowAndRunChainRecord {
    u32 dwOpcode;
    u8 bRespawnRow;
    u8 bChainRow;
} RespawnRowAndRunChainRecord;

void RoomScriptOpRespawnRowAndRunChain(RespawnRowAndRunChainRecord *pRecord)
{
    RespawnRowAndRunChain_candidate(pRecord->bRespawnRow, pRecord->bChainRow);
}

#include "types.h"
#include "overworld/room_script.h"

typedef struct RespawnRowAndRunChainRecord {
    u32 dwOpcode;
    u8 bRespawnRow;
    u8 bChainRow;
} RespawnRowAndRunChainRecord;

void RoomScriptOpRespawnRowAndRunChain(RespawnRowAndRunChainRecord *pRecord)
{
    RespawnGroupAndRunChain(pRecord->bRespawnRow, pRecord->bChainRow);
}

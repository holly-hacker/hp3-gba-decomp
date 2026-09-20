#include "types.h"
#include "room_script.h"

void RoomScriptOpRespawnRowAndRunChain(RoomScriptRecord *pRecord)
{
    RespawnRowAndRunChain_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);
}

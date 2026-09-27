#include "types.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpEnterFredAndGeorgesShop(RoomScriptRecord *pRecord)
{
    g_bPendingRoomScriptChain = pRecord->operand.ab[2];
    g_bPendingRoomScriptRow = pRecord->operand.ab[1];
    PushGameMode_3(FredAndGeorgesShop, 0, pRecord->operand.ab[0], 0);
}

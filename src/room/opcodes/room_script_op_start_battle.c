#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpStartBattle(RoomScriptRecord *pRecord)
{
    g_bRoomScriptCallStackDepth = 0;
    g_bPendingRoomScriptChain = pRecord->operand.ab[2];
    g_bPendingRoomScriptRow = pRecord->operand.ab[1];
    PlaySoundById(6);
    PushGameMode_3(Battle, pRecord->operand.ab[0], 0, 0xff);
}

#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpSetBattleDefeatState(RoomScriptRecord *pRecord)
{
    g_abQuestEventState[0x10] = pRecord->operand.ab[0];
}

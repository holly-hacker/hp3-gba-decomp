#include "types.h"
#include "room_script.h"

void RoomScriptOpConsumeRoomItem(RoomScriptRecord *pRecord)
{
    ConsumeBattleItemSlot(pRecord->operand.ab[0], 1);
}

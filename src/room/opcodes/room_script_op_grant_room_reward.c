#include "types.h"
#include "room_script.h"

void RoomScriptOpGrantRoomReward(RoomScriptRecord *pRecord)
{
    if (pRecord->operand.ab[1] != 0)
        sub_08024A88(pRecord->operand.ab[0]);
    else
        sub_08024A30(pRecord->operand.ab[0]);
}

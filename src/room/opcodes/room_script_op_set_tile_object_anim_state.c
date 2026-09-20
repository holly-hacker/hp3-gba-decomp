#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectAnimState(RoomScriptRecord *pRecord)
{
    SetObjectActionState(GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]), 4);
}

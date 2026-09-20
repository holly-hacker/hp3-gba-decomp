#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectAnimStateValue(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    SetObjectActionState(pObject, pRecord->operand.ab[2]);
    SetObjectActionSubState(pObject, 0);
}

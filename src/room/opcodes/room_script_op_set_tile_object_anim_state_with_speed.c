#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectAnimStateWithSpeed(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    if (pObject != NULL)
    {
        SetObjectActionState(pObject, 0x21);
        SetObjectAnimSubState_candidate(pObject, 0x21);
        pObject->dwUnk_0x28 = 0x28000;
    }
}

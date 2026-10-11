#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectAnimStateWithSpeedRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetTileObjectAnimStateWithSpeedRecord;

void RoomScriptOpSetTileObjectAnimStateWithSpeed(SetTileObjectAnimStateWithSpeedRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pObject != NULL)
    {
        SetActorActionState(pObject, 0x21);
        SetActorAnimSubState_candidate(pObject, 0x21);
        pObject->dwUnk_0x28 = 0x28000;
    }
}

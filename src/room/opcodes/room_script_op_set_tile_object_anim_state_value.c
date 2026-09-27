#include "types.h"
#include "room_script.h"

typedef struct SetTileObjectAnimStateValueRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bActionState;
} SetTileObjectAnimStateValueRecord;

void RoomScriptOpSetTileObjectAnimStateValue(SetTileObjectAnimStateValueRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    SetObjectActionState(pObject, pRecord->bActionState);
    SetObjectActionSubState(pObject, 0);
}

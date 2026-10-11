#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectAnimStateValueRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bActionState;
} SetTileObjectAnimStateValueRecord;

void RoomScriptOpSetTileObjectAnimStateValue(SetTileObjectAnimStateValueRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pObject, pRecord->bActionState);
    SetActorActionSubState(pObject, 0);
}

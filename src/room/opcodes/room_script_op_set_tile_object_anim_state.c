#include "types.h"
#include "room_script.h"

typedef struct SetTileObjectAnimStateRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetTileObjectAnimStateRecord;

void RoomScriptOpSetTileObjectAnimState(SetTileObjectAnimStateRecord *pRecord)
{
    SetObjectActionState(GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY), 4);
}

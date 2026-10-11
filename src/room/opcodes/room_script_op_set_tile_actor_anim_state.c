#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileActorAnimStateRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetTileActorAnimStateRecord;

void RoomScriptOpSetTileActorAnimState(SetTileActorAnimStateRecord *pRecord)
{
    SetActorActionState(GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY), 4);
}

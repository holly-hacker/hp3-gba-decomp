#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileActorAnimStateWithSpeedRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetTileActorAnimStateWithSpeedRecord;

void RoomScriptOpSetTileActorAnimStateWithSpeed(SetTileActorAnimStateWithSpeedRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pActor != NULL)
    {
        SetActorActionState(pActor, 0x21);
        SetActorAnimSubState_candidate(pActor, 0x21);
        pActor->dwUnk_0x28 = 0x28000;
    }
}

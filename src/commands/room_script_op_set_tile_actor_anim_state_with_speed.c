#include "types.h"
#include "area.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct SetTileActorAnimStateWithSpeedRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetTileActorAnimStateWithSpeedRecord;

void RoomScriptOpSetTileActorAnimStateWithSpeed(SetTileActorAnimStateWithSpeedRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    if (pActor != NULL)
    {
        SetActorActionState(pActor, 0x21);
        SetActorPrevActionState(pActor, 0x21);
        pActor->nMoveSpeed = 0x28000;
    }
}

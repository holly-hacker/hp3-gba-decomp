#include "types.h"
#include "area.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct SetTileActorAnimStateValueRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bActionState;
} SetTileActorAnimStateValueRecord;

void RoomScriptOpSetTileActorAnimStateValue(SetTileActorAnimStateValueRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pActor, pRecord->bActionState);
    SetActorActionSubState(pActor, 0);
}

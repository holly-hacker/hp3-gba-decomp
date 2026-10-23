#include "types.h"
#include "area.h"
#include "commands.h"

typedef struct SetTileActorFacingAndScriptPageRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
    u8 bTurnInterval;
} SetTileActorFacingAndScriptPageRecord;

void RoomScriptOpSetTileActorFacingAndScriptPage(SetTileActorFacingAndScriptPageRecord *pRecord)
{
    Actor *pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pActor, 0x1b);
    SetActorActionSubState(pActor, 0);
    if (pActor->dwFlags & ActorFlagFourWayDirections)
        pActor->bFacing = pRecord->bFacing >> 1;
    else
        pActor->bFacing = pRecord->bFacing;
    pActor->scriptState.bytes.bTurnInterval = pRecord->bTurnInterval;
}

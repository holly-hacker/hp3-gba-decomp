#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileActorFacingAndScriptPageRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
    u8 bScriptPageHigh;
} SetTileActorFacingAndScriptPageRecord;

void RoomScriptOpSetTileActorFacingAndScriptPage(SetTileActorFacingAndScriptPageRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pActor, 0x1b);
    SetActorActionSubState(pActor, 0);
    if (pActor->dwFlags & 0x100000)
        pActor->bFacing = pRecord->bFacing >> 1;
    else
        pActor->bFacing = pRecord->bFacing;
    pActor->scriptState.bytes.bScriptPageHigh_candidate = pRecord->bScriptPageHigh;
}

#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectFacingAndScriptPageRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bFacing;
    u8 bScriptPageHigh;
} SetTileObjectFacingAndScriptPageRecord;

void RoomScriptOpSetTileObjectFacingAndScriptPage(SetTileObjectFacingAndScriptPageRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    SetActorActionState(pObject, 0x1b);
    SetActorActionSubState(pObject, 0);
    if (pObject->dwFlags & 0x100000)
        pObject->bFacing = pRecord->bFacing >> 1;
    else
        pObject->bFacing = pRecord->bFacing;
    pObject->scriptState.bytes.bScriptPageHigh_candidate = pRecord->bScriptPageHigh;
}

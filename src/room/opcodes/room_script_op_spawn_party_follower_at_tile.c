#include "types.h"
#include "room_script.h"

void RoomScriptOpSpawnPartyFollowerAtTile(RoomScriptRecord *pRecord)
{
    Object *pObject = sub_0802F6C0(pRecord->operand.ab[0]);

    sub_080236DC(pRecord->operand.ab[0]);
    SetRoomObjectRecordPtr_candidate(pObject, pRecord->operand.ab[1], pRecord->operand.ab[2]);
}

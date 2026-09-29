#include "types.h"
#include "overworld/room_script.h"

typedef struct SpawnPartyFollowerAtTileRecord {
    u32 dwOpcode;
    u8 bCharacterId;
    u8 bTileX;
    u8 bTileY;
} SpawnPartyFollowerAtTileRecord;

void RoomScriptOpSpawnPartyFollowerAtTile(SpawnPartyFollowerAtTileRecord *pRecord)
{
    Object *pObject = sub_0802F6C0(pRecord->bCharacterId);

    sub_080236DC(pRecord->bCharacterId);
    SetRoomObjectRecordPtr_candidate(pObject, pRecord->bTileX, pRecord->bTileY);
}

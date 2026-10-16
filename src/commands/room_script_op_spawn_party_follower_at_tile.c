#include "types.h"
#include "area.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct SpawnPartyFollowerAtTileRecord {
    u32 dwOpcode;
    u8 bCharacterId;
    u8 bTileX;
    u8 bTileY;
} SpawnPartyFollowerAtTileRecord;

void RoomScriptOpSpawnPartyFollowerAtTile(SpawnPartyFollowerAtTileRecord *pRecord)
{
    Actor *pActor = sub_0802F6C0(pRecord->bCharacterId);

    sub_080236DC(pRecord->bCharacterId);
    SetRoomActorPtr(pActor, pRecord->bTileX, pRecord->bTileY);
}

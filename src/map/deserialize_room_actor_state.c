#include "types.h"
#include "save.h"
#include "map.h"

// Reads the saved room-actor snapshot into g_pRoomActorStateBuffer: the
// player's position and switch state, then each table's entry count followed
// by its records.
void DeserializeRoomActorState(void)
{
    s32 i;

    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->playerPos.x, 4);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->playerPos.y, 4);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bPlayerFacing, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bDefaultCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bTriggerZoneCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bWorldActorCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bTileAnimationCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bWorldActorSwitchCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bFlamePillarCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bPresenceMarkerCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bSwitchState, 1);

    for (i = 0; i < g_pRoomActorStateBuffer->bDefaultCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aDefault[i], sizeof(RoomActorDefaultRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bTriggerZoneCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aTriggerZone[i], sizeof(RoomActorTriggerZoneRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bWorldActorCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aWorldActor[i], sizeof(RoomActorWorldActorRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bTileAnimationCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aTileAnimation[i], sizeof(RoomActorTileAnimationRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bWorldActorSwitchCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aWorldActorSwitch[i], sizeof(RoomActorSwitchRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bFlamePillarCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aFlamePillar[i], sizeof(RoomActorFlamePillarRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bPresenceMarkerCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aPresenceMarker[i], sizeof(RoomActorTileRecord));
}

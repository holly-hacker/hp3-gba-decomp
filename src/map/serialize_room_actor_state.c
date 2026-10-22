#include "types.h"
#include "save.h"
#include "map.h"

// Writes g_pRoomActorStateBuffer's room-actor snapshot: the
// player's position and switch state, then each table's entry count followed
// by its records.
void SerializeRoomActorState(void)
{
    s32 i;

    PackBytesToSaveStream(&g_pRoomActorStateBuffer->playerPos.x, 4);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->playerPos.y, 4);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bPlayerFacing, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bDefaultCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bTriggerZoneCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bWorldActorCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bTileAnimationCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bWorldActorSwitchCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bFlamePillarCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bPresenceMarkerCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bSwitchState, 1);

    for (i = 0; i < g_pRoomActorStateBuffer->bDefaultCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aDefault[i], sizeof(RoomActorDefaultRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bTriggerZoneCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aTriggerZone[i], sizeof(RoomActorTriggerZoneRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bWorldActorCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aWorldActor[i], sizeof(RoomActorWorldActorRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bTileAnimationCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aTileAnimation[i], sizeof(RoomActorTileAnimationRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bWorldActorSwitchCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aWorldActorSwitch[i], sizeof(RoomActorSwitchRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bFlamePillarCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aFlamePillar[i], sizeof(RoomActorFlamePillarRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bPresenceMarkerCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aPresenceMarker[i], sizeof(RoomActorTileRecord));
}

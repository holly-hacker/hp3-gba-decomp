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
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bKind4Or7Count, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bKind5Count, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bFloorItemCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bKind5SwitchCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bPickupMarkerCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bPresenceMarkerCount, 1);
    PackBytesToSaveStream(&g_pRoomActorStateBuffer->bSwitchState, 1);

    for (i = 0; i < g_pRoomActorStateBuffer->bDefaultCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aDefault[i], sizeof(RoomActorDefaultRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bKind4Or7Count; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aKind4Or7[i], sizeof(RoomActorKind4Or7Record));
    for (i = 0; i < g_pRoomActorStateBuffer->bKind5Count; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aKind5[i], sizeof(RoomActorKind5Record));
    for (i = 0; i < g_pRoomActorStateBuffer->bFloorItemCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aFloorItem[i], sizeof(RoomActorFloorItemRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bKind5SwitchCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aKind5Switch[i], sizeof(RoomActorSwitchRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bPickupMarkerCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aPickupMarker[i], sizeof(RoomActorPickupRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bPresenceMarkerCount; i++)
        PackBytesToSaveStream(&g_pRoomActorStateBuffer->aPresenceMarker[i], sizeof(RoomActorTileRecord));
}

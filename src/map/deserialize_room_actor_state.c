#include "types.h"
#include "save.h"
#include "map.h"

// Reads the saved room-actor snapshot into g_pRoomActorStateBuffer: the
// player's position and switch state, then each table's entry count followed
// by its records (see docs/formats/save.md for the table meanings).
void DeserializeRoomActorState(void)
{
    s32 i;

    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->playerPos.x, 4);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->playerPos.y, 4);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bPlayerFacing, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bDefaultCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bKind4Or7Count, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bKind5Count, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bFloorItemCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bKind5SwitchCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bPickupMarkerCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bPresenceMarkerCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->bSwitchState, 1);

    for (i = 0; i < g_pRoomActorStateBuffer->bDefaultCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aDefault[i], sizeof(RoomActorDefaultRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bKind4Or7Count; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aKind4Or7[i], sizeof(RoomActorKind4Or7Record));
    for (i = 0; i < g_pRoomActorStateBuffer->bKind5Count; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aKind5[i], sizeof(RoomActorKind5Record));
    for (i = 0; i < g_pRoomActorStateBuffer->bFloorItemCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aFloorItem[i], sizeof(RoomActorFloorItemRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bKind5SwitchCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aKind5Switch[i], sizeof(RoomActorSwitchRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bPickupMarkerCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aPickupMarker[i], sizeof(RoomActorPickupRecord));
    for (i = 0; i < g_pRoomActorStateBuffer->bPresenceMarkerCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomActorStateBuffer->aPresenceMarker[i], sizeof(RoomActorTileRecord));
}

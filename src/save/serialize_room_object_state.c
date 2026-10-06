#include "types.h"
#include "game/save.h"
#include "overworld/room.h"

// Writes g_pRoomObjectStateBuffer's room-object snapshot: the
// player's position and switch state, then each table's entry count followed
// by its records (see docs/formats/save.md for the table meanings).
void SerializeRoomObjectState(void)
{
    s32 i;

    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->fxPlayerPosX, 4);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->fxPlayerPosY, 4);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bPlayerFacing, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bDefaultCount, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bKind4Or7Count, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bKind5Count, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bFloorItemCount, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bKind5SwitchCount, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bPickupMarkerCount, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bPresenceMarkerCount, 1);
    PackBytesToSaveStream(&g_pRoomObjectStateBuffer->bSwitchState, 1);

    for (i = 0; i < g_pRoomObjectStateBuffer->bDefaultCount; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aDefault[i], sizeof(RoomObjectDefaultRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bKind4Or7Count; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aKind4Or7[i], sizeof(RoomObjectKind4Or7Record));
    for (i = 0; i < g_pRoomObjectStateBuffer->bKind5Count; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aKind5[i], sizeof(RoomObjectKind5Record));
    for (i = 0; i < g_pRoomObjectStateBuffer->bFloorItemCount; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aFloorItem[i], sizeof(RoomObjectFloorItemRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bKind5SwitchCount; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aKind5Switch[i], sizeof(RoomObjectTileRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bPickupMarkerCount; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aPickupMarker[i], sizeof(RoomObjectTileRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bPresenceMarkerCount; i++)
        PackBytesToSaveStream(&g_pRoomObjectStateBuffer->aPresenceMarker[i], sizeof(RoomObjectTileRecord));
}

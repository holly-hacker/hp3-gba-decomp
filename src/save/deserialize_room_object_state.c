#include "types.h"
#include "game/save.h"
#include "overworld/room.h"

// Reads the saved room-object snapshot into g_pRoomObjectStateBuffer: the
// player's position and switch state, then each table's entry count followed
// by its records (see docs/formats/save.md for the table meanings).
void DeserializeRoomObjectState(void)
{
    s32 i;

    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->fxPlayerPosX, 4);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->fxPlayerPosY, 4);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bPlayerFacing, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bDefaultCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bKind4Or7Count, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bKind5Count, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bFloorItemCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bKind5SwitchCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bPickupMarkerCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bPresenceMarkerCount, 1);
    UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->bSwitchState, 1);

    for (i = 0; i < g_pRoomObjectStateBuffer->bDefaultCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aDefault[i], sizeof(RoomObjectDefaultRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bKind4Or7Count; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aKind4Or7[i], sizeof(RoomObjectKind4Or7Record));
    for (i = 0; i < g_pRoomObjectStateBuffer->bKind5Count; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aKind5[i], sizeof(RoomObjectKind5Record));
    for (i = 0; i < g_pRoomObjectStateBuffer->bFloorItemCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aFloorItem[i], sizeof(RoomObjectFloorItemRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bKind5SwitchCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aKind5Switch[i], sizeof(RoomObjectTileRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bPickupMarkerCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aPickupMarker[i], sizeof(RoomObjectTileRecord));
    for (i = 0; i < g_pRoomObjectStateBuffer->bPresenceMarkerCount; i++)
        UnpackBytesFromSaveStream(&g_pRoomObjectStateBuffer->aPresenceMarker[i], sizeof(RoomObjectTileRecord));
}

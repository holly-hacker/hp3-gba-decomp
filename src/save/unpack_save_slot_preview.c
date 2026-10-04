#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Unpacks the leading fields SerializeGameStateToSaveBuffer writes into a
// slot's stream (money, playtime, room, save flags, objective, leader level).
void UnpackSaveSlotPreview(SaveSlotPreview *preview)
{
    memset(preview, 0, sizeof(SaveSlotPreview));
    UnpackBytesFromSaveStream(&preview->dwMoney, 4);
    UnpackBytesFromSaveStream(&preview->bPlaytimeHours, 4);
    UnpackBytesFromSaveStream(&preview->bCurrentRoomId, 1);
    UnpackBytesFromSaveStream(&preview->bSaveFlags, 1);
    UnpackBytesFromSaveStream(&preview->bMainMenuObjectiveIndex, 1);
    UnpackBytesFromSaveStream(&preview->bPartyLeaderDisplayLevel, 1);
}

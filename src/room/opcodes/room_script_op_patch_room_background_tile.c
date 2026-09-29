#include "types.h"
#include "overworld/room_script.h"

typedef struct PatchRoomBackgroundTileRecord {
    u32 dwOpcode;
    u16 wX;
    u16 wY;
    u16 wTileId;
    u8 bLayer;
} PatchRoomBackgroundTileRecord;

void RoomScriptOpPatchRoomBackgroundTile(PatchRoomBackgroundTileRecord *pRecord)
{
    WriteRoomBgTile_candidate(pRecord->wX, pRecord->wY, pRecord->wTileId, pRecord->bLayer);
}

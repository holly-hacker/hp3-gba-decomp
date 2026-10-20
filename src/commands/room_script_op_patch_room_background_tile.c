#include "types.h"
#include "commands.h"
#include "scroll.h"

typedef struct PatchRoomBackgroundTileRecord {
    u32 dwOpcode;
    u16 wX;
    u16 wY;
    u16 wTileId;
    u8 bLayer;
} PatchRoomBackgroundTileRecord;

void RoomScriptOpPatchRoomBackgroundTile(PatchRoomBackgroundTileRecord *pRecord)
{
    WriteRoomBgBlock(pRecord->wX, pRecord->wY, pRecord->wTileId, pRecord->bLayer);
}

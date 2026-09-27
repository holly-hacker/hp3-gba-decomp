#include "types.h"
#include "room.h"
#include "room_script.h"

typedef struct SetCameraFollowTileObjectRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetCameraFollowTileObjectRecord;

// No room script uses this opcode.
void RoomScriptOpSetCameraFollowTileObject(SetCameraFollowTileObjectRecord *pRecord)
{
    // Never initialized: the offset is whatever the interpreter left in r4/r5, which both hold
    // the current record's address at dispatch.
    CameraFocusOffset offset;

    SetCameraFollowTarget_candidate(GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY), offset, 0);
}

#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct SetCameraFollowTileActorRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} SetCameraFollowTileActorRecord;

// No room script uses this opcode.
void RoomScriptOpSetCameraFollowTileActor(SetCameraFollowTileActorRecord *pRecord)
{
    // Never initialized: the offset is whatever the interpreter left in r4/r5, which both hold
    // the current record's address at dispatch.
    CameraFocusOffset offset;

    SetCameraFollowTarget_candidate(GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY), offset, 0);
}

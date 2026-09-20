#include "types.h"
#include "room_script.h"

void RoomScriptOpPatchRoomBackgroundTile(RoomScriptRecord *pRecord)
{
    WriteRoomBgTile_candidate(pRecord->operand.aw[0], pRecord->operand.aw[1], pRecord->operand.aw[2],
                              pRecord->operand.ab[6]);
}

#include "types.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

void RoomScriptOpClearOverworldMonstersDisabled(RoomScriptRecord *pRecord)
{
    g_dwOverworldMonstersDisabled = 0;
}

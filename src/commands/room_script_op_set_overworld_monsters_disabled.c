#include "types.h"
#include "commands.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

void RoomScriptOpSetOverworldMonstersDisabled(RoomScriptRecord *pRecord)
{
    g_dwOverworldMonstersDisabled = 1;
}

#include "types.h"
#include "room.h"
#include "room_script.h"

void RoomScriptOpSetOverworldMonstersDisabled(RoomScriptRecord *pRecord)
{
    g_dwOverworldMonstersDisabled = 1;
}

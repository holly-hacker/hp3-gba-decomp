#include "commands.h"
#include "overworld/room_script.h"
#include "combat.h"

void RoomScriptOpClearOverworldMonstersDisabled(RoomScriptRecord *pRecord)
{
    g_dwOverworldMonstersDisabled = 0;
}

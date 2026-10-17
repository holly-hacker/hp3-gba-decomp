#include "commands.h"
#include "overworld/room_script.h"
#include "combat.h"

void RoomScriptOpSetOverworldMonstersDisabled(RoomScriptRecord *pRecord)
{
    g_dwOverworldMonstersDisabled = 1;
}

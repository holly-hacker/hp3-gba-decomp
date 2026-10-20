#include "commands.h"
#include "modes.h"
#include "overworld/room_script.h"
#include "main.h"

void RoomScriptOpOpenMainMenu(RoomScriptRecord *pRecord)
{
    PushGameMode(MainMenu);
    g_dwGameModeFlags |= GameModeFlagModeChangeRequested;
}

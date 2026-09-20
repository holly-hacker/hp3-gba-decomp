#include "types.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpOpenMainMenu(RoomScriptRecord *pRecord)
{
    PushGameMode(MainMenu);
    g_dwGameModeFlags |= 0x80000000;
}

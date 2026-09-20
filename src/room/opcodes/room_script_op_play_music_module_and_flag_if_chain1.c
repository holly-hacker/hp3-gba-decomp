#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpPlayMusicModuleAndFlagIfChain1(RoomScriptRecord *pRecord)
{
    if (g_bRoomScriptCurrentRow == 1)
        g_dwGameModeFlags |= 0x1000000;
    PlayMusicModule(pRecord->operand.ab[0]);
}

#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "overworld/room_script.h"

typedef struct PlayMusicModuleAndFlagIfChain1Record {
    u32 dwOpcode;
    u8 bModuleId;
} PlayMusicModuleAndFlagIfChain1Record;

void RoomScriptOpPlayMusicModuleAndFlagIfChain1(PlayMusicModuleAndFlagIfChain1Record *pRecord)
{
    if (g_bRoomScriptCurrentRow == 1)
        g_dwGameModeFlags |= 0x1000000;
    PlayMusicModule(pRecord->bModuleId);
}

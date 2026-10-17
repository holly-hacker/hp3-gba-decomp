#include "types.h"
#include "commands.h"
#include "graphics/audio.h"
#include "modes.h"
#include "overworld/room_script.h"

typedef struct PlayMusicModuleAndFlagIfChain1Record {
    u32 dwOpcode;
    u8 bModuleId;
} PlayMusicModuleAndFlagIfChain1Record;

void RoomScriptOpPlayMusicModuleAndFlagIfChain1(PlayMusicModuleAndFlagIfChain1Record *pRecord)
{
    // InitializeOverworld clears this bit and skips its room-music selection when it is set.
    if (g_bRoomScriptCurrentChain == 1)
        g_dwGameModeFlags |= 0x1000000;
    PlayMusicModule(pRecord->bModuleId);
}

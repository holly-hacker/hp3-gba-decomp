#include "types.h"
#include "commands.h"
#include "sound.h"
#include "area.h"
#include "main.h"

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

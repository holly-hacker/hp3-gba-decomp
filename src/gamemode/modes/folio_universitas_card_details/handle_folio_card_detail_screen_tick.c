#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "hw/input.h"

void HandleFolioCardDetailScreenTick(void)
{
    if (g_wKeysPressed & (KeyA | KeyB))
    {
        PlaySoundById(2);
        PushGameMode_2(FolioUniversitas, g_GameModeStackContext.dwCurrentGameModeArg1,
                       g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}

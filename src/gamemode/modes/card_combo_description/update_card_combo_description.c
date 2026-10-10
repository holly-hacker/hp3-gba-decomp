#include "types.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "input.h"
#include "menu/main_menu.h"

void UpdateCardComboDescription(void)
{
    sub_0801E0D8();

    if (g_wKeysPressed & (KeyA | KeyB))
    {
        PlaySoundById(2);
        PushGameMode_3(FolioUniversitas, g_GameModeStackContext.dwCurrentGameModeArg1,
                       g_GameModeStackContext.dwCurrentGameModeArg2, 0);
    }
}

#include "combo_info.h"
#include "modes.h"
#include "sound.h"
#include "input.h"
#include "default_menu.h"

void UpdateCardComboDescription(void)
{
    UpdateMenuScreen();

    if (g_wKeysPressed & (KeyA | KeyB))
    {
        PlaySoundById(2);
        PushGameMode_3(FolioUniversitas, g_GameModeStackContext.dwCurrentGameModeArg1,
                       g_GameModeStackContext.dwCurrentGameModeArg2, 0);
    }
}

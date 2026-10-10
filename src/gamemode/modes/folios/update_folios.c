#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "input.h"
#include "menu/folios.h"
#include "menu/in_game_menu.h"

void UpdateFolios(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & KeyA)
        {
            SelectInGameMenuEntry_candidate();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            MoveListMenuCursor();
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            g_GameModeStackContext.dwModeSubState = 0;
            SetAlphaBlendCoefficients(0x10, 0);
            SetAlphaBlendTargets(0x14, 1);
            g_GameModeStackContext.dwModeState = 4;
        }
        break;

    case 4:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(InGameMenuFadeIn);
        break;
    }
}

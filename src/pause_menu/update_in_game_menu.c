#include "sound.h"
#include "modes.h"
#include "pause_menu.h"
#include "input.h"
#include "default_menu.h"
#include "pscreen_character.h"
#include "map.h"

void UpdateInGameMenu(void)
{
    UpdateMenuScreen();

    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            if (g_GameModeStackContext.dwModeState == 0)
            {
                g_GameModeStackContext.dwModeState = 1;
                StartMenuFadeIn();
                BuildListMenu(&g_InGameMenuDefinition);
            }
            else
                g_GameModeStackContext.dwModeState = 2;
        }
        break;

    case 2:
        if (g_wKeysPressed & KeyA)
        {
            if (g_GameModeStackContext.dwModeScratchB == 0)
                NoopStatusEquipSelected();
            SelectListMenuEntry();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            MoveListMenuCursor();
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            PushGameMode_2(Overworld, OverworldEntryRestore, g_bCurrentRoomId);
        }
        break;

    case 3:
    case 4:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            ExitPauseMenuScreen();
            if (g_GameModeStackContext.dwModeState == 3)
            {
                g_GameModeStackContext.dwModeState = 4;
                StartMenuOverlayFadeOut();
            }
            else
            {
                if (g_aInGameMenuEntries[g_GameModeStackContext.dwModeScratchB].dwImmediate != 0)
                    g_StatusEquipReturnMode = InGameMenu;
                else
                    g_StatusEquipReturnMode = InGameMenuFadeIn;

                if (g_GameModeStackContext.dwModeScratchB == 0)
                    g_StatusEquipNextMode = StatusEquipSlotSelect;
                else
                    g_StatusEquipNextMode = 0;

                PushGameMode(g_aInGameMenuEntries[g_GameModeStackContext.dwModeScratchB].mode);
            }
        }
        break;
    }
}

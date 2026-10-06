#include "types.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "hw/input.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "menu/help.h"
#include "menu/in_game_menu.h"

void UpdateHelp(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            SetAlphaBlendTargets(4, 1);
            g_GameModeStackContext.dwModeState = 2;
        }
        break;

    case 2:
        if (g_wKeysPressed & KeyB)
            CancelHelpScreen();

        switch (g_HelpState.bPageKind)
        {
        case HelpPageMenu:
            if (g_wKeysPressed & KeyA)
            {
                OpenSelectedHelpMenuEntry();
            }
            else if (g_wKeysPressed & KeyUp)
            {
                SetHelpMenuSelection((g_HelpState.bSelectedEntry == 0 ? g_HelpState.dwEntryCount
                                                                      : g_HelpState.bSelectedEntry)
                                     - 1);
                PlaySoundById(0);
            }
            else if (g_wKeysPressed & KeyDown)
            {
                SetHelpMenuSelection(g_HelpState.bSelectedEntry == g_HelpState.dwEntryCount - 1
                                         ? 0
                                         : g_HelpState.bSelectedEntry + 1);
                PlaySoundById(0);
            }
            break;

        case HelpPageText:
            if (g_wKeysPressed & KeyLeft)
                TurnToPrevHelpPage();
            else if (g_wKeysPressed & KeyRight)
                TurnToNextHelpPage();
            break;
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 14 && g_HelpState.pPendingPage == NULL
            && g_HelpState.bPageDepth == 0)
            ClearHelpScreen();

        if (g_GameModeStackContext.dwModeSubState == 16)
        {
            ClearHelpScreen();
            g_GameModeStackContext.dwModeState = 4;
        }
        break;

    case 4:
        if (g_HelpState.pPendingPage == NULL)
        {
            if (g_HelpState.bPageDepth == 0)
            {
                ClearHelpScreen();
                FreeAllObjects(&g_ActiveObjectListState.pHead);
                while (!(REG_DISPSTAT & 2))
                    ;
                g_GameModeStackContext.dwModeSubState = 0;
                SetAlphaBlendTargets(0x14, 1);
                SetAlphaBlendCoefficients(16 - g_GameModeStackContext.dwModeSubState,
                                          g_GameModeStackContext.dwModeSubState);
                FreeHelpScreen();
                g_GameModeStackContext.dwModeState = 5;
                break;
            }

            g_HelpState.bPageDepth--;
            g_HelpState.bSelectedEntry = g_HelpState.aPageStack[g_HelpState.bPageDepth].dwSelectedEntry;
            RunHelpScript(g_HelpState.aPageStack[g_HelpState.bPageDepth].pPage);
            g_GameModeStackContext.dwModeSubState = 16;
            g_GameModeStackContext.dwModeState = 1;
        }
        else
        {
            g_HelpState.bSelectedEntry = 0;
            RunHelpScript(g_HelpState.pPendingPage);
            g_GameModeStackContext.dwModeSubState = 16;
            g_GameModeStackContext.dwModeState = 1;
        }
        break;

    case 5:
        PushGameMode_3(g_HelpState.dwExitMode, g_HelpState.dwExitArg1, g_HelpState.dwExitArg2,
                       g_HelpState.dwExitArg3);
        break;
    }
}

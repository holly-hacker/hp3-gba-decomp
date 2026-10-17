#include "sound.h"
#include "modes.h"
#include "pscreen_save.h"
#include "input.h"
#include "pause_menu.h"
#include "save.h"
#include "screen_transitions.h"

void UpdateGameSave(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 2:
        if (--g_GameModeStackContext.dwModeTimer == 0)
        {
            SyncSaveHeaderIfDirty();
            SaveGameToSlot(g_saveManager.dwActiveSlot);
            SetAlphaBlendTargets(4, 2);
            SetAlphaBlendCoefficients(0x10, 0);
            g_GameModeStackContext.dwModeState = 3;
            g_GameModeStackContext.dwModeSubState = 0;
        }
        break;

    case 3:
        g_GameModeStackContext.dwModeSubState += 2;
        SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                                  g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            ShowGameSavedMessage_candidate();
            g_GameModeStackContext.dwModeState = 4;
        }
        break;

    case 4:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 5;
        break;

    case 5:
        if (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart | KeyR | KeyL))
        {
            PlaySoundById(1);
            if (g_PrevGameModeStackContext.dwCurrentGameMode == InGameMenu
                || g_PrevGameModeStackContext.dwCurrentGameMode == InGameMenuFadeIn)
                PushGameMode(InGameMenu);
            else
                PushGameMode(MainMenu);
        }
        break;

    case 8:
        if (g_wKeysPressed & KeyA)
        {
            ResolveSaveConfirmation_candidate();
        }
        else if (g_wKeysPressed & KeyB)
        {
            g_GameModeStackContext.dwModeScratchB = 0;
            ResolveSaveConfirmation_candidate();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            MoveListMenuCursor();
        }
        break;
    }
}

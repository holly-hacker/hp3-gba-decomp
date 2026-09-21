#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "game_save.h"
#include "input.h"
#include "main_menu.h"
#include "save.h"

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
        TickBlendFadeOut_candidate();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 5;
        break;

    case 5:
        if (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart | KeyR | KeyL))
        {
            PlaySoundById(1);
            if (g_PrevGameModeCtx.dwCurrentGameMode == InGameMenu
                || g_PrevGameModeCtx.dwCurrentGameMode == InGameMenuFadeIn)
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
            sub_0803227C();
        }
        break;
    }
}

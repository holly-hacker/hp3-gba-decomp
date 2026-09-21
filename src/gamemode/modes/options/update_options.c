#include "types.h"
#include "audio.h"
#include "battle.h"
#include "game_modes.h"
#include "input.h"
#include "main_menu.h"
#include "options.h"
#include "save.h"
#include "text.h"

void UpdateOptions(void)
{
    if (g_GameModeStackContext.dwModeTimer_candidate != 0)
    {
        g_GameModeStackContext.dwModeTimer_candidate--;
        return;
    }

    sub_0801E0D8();

    if (g_GameModeStackContext.dwModeState_candidate != 0)
        return;

    if (g_wKeysPressed & (KeyB | KeySelect | KeyStart))
    {
        if (g_wKeysPressed & KeyStart)
        {
            g_saveManager.header.bMusicVolume = g_OptionsState.dwMusicVolume;
            g_saveManager.header.bSoundVolume = g_OptionsState.dwSoundVolume;
            g_saveManager.header.bHeaderFlags.bGammaHigh = g_OptionsState.dwGammaHigh;
            PlaySoundById(1);
        }
        else
        {
            PlaySoundById(2);
            if (g_dwOptionsEntryLanguage != GetLanguage())
            {
                SetLanguage(g_dwOptionsEntryLanguage);
                SetSaveLanguageFlag();
                DisableKrawall();
                SyncSaveHeaderIfDirty();
                EnableKrawall();
            }
        }

        SetSoundEffectVolume((u8)(g_saveManager.header.bMusicVolume * 25));
        SetMusicVolume((u8)(g_saveManager.header.bSoundVolume * 12), 0);

        switch (g_dwOptionsReturnMode)
        {
        case Overworld:
            PushGameMode_2(Overworld, 2, g_bCurrentRoomId);
            break;
        case MainMenu:
            PushGameMode_2(MainMenu, 0, g_PrevGameModeCtx.dwModeScratchB_candidate);
            g_dwPendingGameMode.dwCurrentGameModeArg2 = MainMenuOptions;
            break;
        }
    }
    else if (g_wKeysPressed & KeyA)
    {
        switch (g_GameModeStackContext.dwModeScratchB_candidate)
        {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
            PlaySoundById(1);
            g_bOptionsSavedMusicVolume = g_OptionsState.dwMusicVolume;
            g_bOptionsSavedSoundVolume = g_OptionsState.dwSoundVolume;
            g_bOptionsSavedGammaHigh = g_OptionsState.dwGammaHigh;
            PushGameMode(LanguageSelect);
            break;
        }
    }
    else if (g_wKeysPressed & (KeyUp | KeyDown))
        MoveOptionsCursor_candidate();
    else if (g_wKeysPressed & (KeyLeft | KeyRight))
        AdjustOptionValue_candidate();
}

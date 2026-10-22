#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "title.h"
#include "title_options.h"
#include "save.h"
#include "text.h"
#include "default_menu.h"
#include "map.h"

void UpdateOptions(void)
{
    if (g_GameModeStackContext.dwModeTimer != 0)
    {
        g_GameModeStackContext.dwModeTimer--;
        return;
    }

    UpdateMenuScreen();

    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (g_wKeysPressed & (KeyB | KeySelect | KeyStart))
    {
        if (g_wKeysPressed & KeyStart)
        {
            g_saveManager.header.bMusicVolume = g_OptionsState.adwValues[OptionsRowSound];
            g_saveManager.header.bSoundVolume = g_OptionsState.adwValues[OptionsRowMusic];
            g_saveManager.header.bHeaderFlags.bits.bGammaHigh = g_OptionsState.adwValues[OptionsRowGamma];
            PlaySoundById(1);
        }
        else
        {
            PlaySoundById(2);
#ifndef VERSION_JP
            if (g_dwOptionsEntryLanguage != GetLanguage())
            {
                SetLanguage(g_dwOptionsEntryLanguage);
                SetSaveLanguageFlag();
                DisableKrawall();
                SyncSaveHeaderIfDirty();
                EnableKrawall();
            }
#endif
        }

        SetSoundEffectVolume((u8)(g_saveManager.header.bMusicVolume * 25));
        SetMusicVolume((u8)(g_saveManager.header.bSoundVolume * 12), 0);

        switch (g_dwOptionsReturnMode)
        {
        case Overworld:
            PushGameMode_2(Overworld, OverworldEntryRestore, g_bCurrentRoomId);
            break;
        case MainMenu:
            PushGameMode_2(MainMenu, 0, g_PrevGameModeStackContext.dwModeScratchB);
            g_dwPendingGameMode.dwCurrentGameModeArg2 = MainMenuOptions;
            break;
        }
    }
    else if (g_wKeysPressed & KeyA)
    {
#ifndef VERSION_JP
        switch (g_GameModeStackContext.dwModeScratchB)
        {
        case OptionsRowSound:
        case OptionsRowMusic:
        case OptionsRowGamma:
            break;
        case OptionsRowLanguage:
            PlaySoundById(1);
            g_bOptionsSavedMusicVolume = g_OptionsState.adwValues[OptionsRowSound];
            g_bOptionsSavedSoundVolume = g_OptionsState.adwValues[OptionsRowMusic];
            g_bOptionsSavedGammaHigh = g_OptionsState.adwValues[OptionsRowGamma];
            PushGameMode(LanguageSelect);
            break;
        }
#endif
    }
    else if (g_wKeysPressed & (KeyUp | KeyDown))
        MoveOptionsCursor();
    else if (g_wKeysPressed & (KeyLeft | KeyRight))
        AdjustOptionValue();
}

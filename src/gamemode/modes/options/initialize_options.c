#include "types.h"
#include "graphics/display.h"
#include "modes.h"
#include "particles.h"
#include "actor.h"
#include "menu/options.h"
#include "save.h"
#include "text.h"
#include "cursor.h"
#include "default_menu.h"
#include "screen_transitions.h"

void InitializeOptions(void)
{

    SetAlphaBlendTargets(0, 0);
    ClearObjPaletteSlots();

#ifdef VERSION_JP
    g_dwOptionsReturnMode = g_PrevGameModeStackContext.dwCurrentGameMode;

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwModeTimer = 3;

    g_OptionsState.dwMusicVolume = g_saveManager.header.bMusicVolume;
    g_OptionsState.dwSoundVolume = g_saveManager.header.bSoundVolume;
    g_OptionsState.dwGammaHigh = g_saveManager.header.bHeaderFlags.bits.bGammaHigh;
    g_GameModeStackContext.dwModeScratchB = 0;
#else
    if (g_PrevGameModeStackContext.dwCurrentGameMode != LanguageSelect)
    {
        g_dwOptionsEntryLanguage = GetLanguage();
        if (g_PrevGameModeStackContext.dwCurrentGameMode != LanguageSelect)
            g_dwOptionsReturnMode = g_PrevGameModeStackContext.dwCurrentGameMode;
    }

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwModeTimer = 3;

    if (g_PrevGameModeStackContext.dwCurrentGameMode == LanguageSelect)
    {
        g_OptionsState.dwMusicVolume = g_bOptionsSavedMusicVolume;
        g_OptionsState.dwSoundVolume = g_bOptionsSavedSoundVolume;
        g_OptionsState.dwGammaHigh = g_bOptionsSavedGammaHigh;
        g_GameModeStackContext.dwModeScratchB = 3;
    }
    else
    {
        g_OptionsState.dwMusicVolume = g_saveManager.header.bMusicVolume;
        g_OptionsState.dwSoundVolume = g_saveManager.header.bSoundVolume;
        g_OptionsState.dwGammaHigh = g_saveManager.header.bHeaderFlags.bits.bGammaHigh;
        g_GameModeStackContext.dwModeScratchB = 0;
    }
#endif

    InitializeMenuScreen(0x8CF, 4, 1, gMenuScreenGraphic, 0, 1);  // "Options"
    g_pMenuCursorActor->oam.objMode = 1;
    g_pMenuCursorActor->oam.hFlip = 1;
    SetMenuCursorPosition(g_pMenuCursorActor,
                 g_aOptionsMenuItems[g_GameModeStackContext.dwModeScratchB].nX - 0xE,
                 g_aOptionsMenuItems[g_GameModeStackContext.dwModeScratchB].nY + 8);
    BuildOptionsScreen_candidate();
    PlayScreenTransitionInByIndex(0x3F, 2);
}

#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "graphics.h"
#include "main_menu.h"
#include "object.h"
#include "options.h"
#include "save.h"
#include "text.h"

void InitializeOptions(void)
{
    ObjectFlagsD1 *pFlags;
    ObjectFlagsD3 *pFlagsD3;

    SetAlphaBlendTargets(0, 0);
    ClearResourceCacheSlots();

    if (g_PrevGameModeCtx.dwCurrentGameMode != LanguageSelect)
    {
        g_dwOptionsEntryLanguage = GetLanguage();
        if (g_PrevGameModeCtx.dwCurrentGameMode != LanguageSelect)
            g_dwOptionsReturnMode = g_PrevGameModeCtx.dwCurrentGameMode;
    }

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwModeTimer = 3;

    if (g_PrevGameModeCtx.dwCurrentGameMode == LanguageSelect)
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

    sub_0801DF6C(0x8CF, 4, 1, g_MenuScreenGraphic, 0, 1);  // "Options"
    pFlags = (ObjectFlagsD1 *)&g_pMenuCursorObject->bFlags_0xD1;
    pFlags->bField2To3_candidate = 1;
    pFlagsD3 = (ObjectFlagsD3 *)&g_pMenuCursorObject->bAffineFlagsHigh;
    pFlagsD3->bXFlip = 1;
    sub_0801DCC4(g_pMenuCursorObject,
                 g_aOptionsMenuItems[g_GameModeStackContext.dwModeScratchB].nX - 0xE,
                 g_aOptionsMenuItems[g_GameModeStackContext.dwModeScratchB].nY + 8);
    BuildOptionsScreen_candidate();
    PlayScreenTransitionInByIndex_candidate(0x3F, 2);
}

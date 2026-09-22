#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "save.h"
#include "text.h"

void InitializeLanguageSelect(void)
{
    ResetDisplayState(0);
    SetBgControl(3, g_dwLanguageSelectBg3Control);
    SetBgControl(2, g_dwLanguageSelectBg2Control);
    SetBgControl(1, g_dwLanguageSelectBg1Control);

    LoadBgGraphic(3, g_MenuBg3Graphic, 1, 0, 0, 0);
    SetBgScroll_candidate(3, 8, 0);
    sub_08007464(2, 0x78);
    LoadBgGraphic(2, g_LanguageSelectBg2Graphic, 0x79, 0, 0, 10);
    ClearBgTilemap(1);
    LoadBgGraphic(1, g_LanguageSelectBg1Graphic, 1, 0, 0, 0x14);

    g_GameModeStackContext.dwModeScratchB =
        (g_saveManager.header.bLanguageByte & 0x80) ? GetLanguage() : 0;

    DrawLanguageSelectEntries_candidate();
    DrawLanguageSelectPicture_candidate(g_GameModeStackContext.dwModeScratchB);

    if (g_PrevGameModeStackContext.dwCurrentGameMode == 0)
        PlayScreenTransitionInByIndex(0x3F, 1);
    else
        PlayScreenTransitionInByIndex(0x3F, 2);

    g_GameModeStackContext.dwModeTimer = 3;
}

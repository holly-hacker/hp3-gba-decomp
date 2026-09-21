#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "save.h"
#include "text.h"

void InitializeLanguageSelect(void)
{
    ResetDisplayState_candidate(0);
    SetBgControl_candidate(3, g_dwLanguageSelectBg3Control);
    SetBgControl_candidate(2, g_dwLanguageSelectBg2Control);
    SetBgControl_candidate(1, g_dwLanguageSelectBg1Control);

    LoadBgGraphic_candidate(3, g_MenuBg3Graphic, 1, 0, 0, 0);
    sub_08007B88(3, 8, 0);
    sub_08007464(2, 0x78);
    LoadBgGraphic_candidate(2, g_LanguageSelectBg2Graphic, 0x79, 0, 0, 10);
    ClearBgTilemap_candidate(1);
    LoadBgGraphic_candidate(1, g_LanguageSelectBg1Graphic, 1, 0, 0, 0x14);

    g_GameModeStackContext.dwModeScratchB_candidate =
        (g_saveHeader.bLanguageByte & 0x80) ? GetLanguage() : 0;

    DrawLanguageSelectEntries_candidate();
    DrawLanguageSelectPicture_candidate(g_GameModeStackContext.dwModeScratchB_candidate);

    if (g_PrevGameModeCtx.dwCurrentGameMode == 0)
        PlayScreenTransitionInByIndex_candidate(0x3F, 1);
    else
        PlayScreenTransitionInByIndex_candidate(0x3F, 2);

    g_GameModeStackContext.dwModeTimer_candidate = 3;
}

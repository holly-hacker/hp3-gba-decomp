#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "text.h"

void InitializeStartup(void)
{
    u32 bgCtrl2;
    u32 cursor;
    u8 *pText;

    ResetDisplayState_candidate(0);
    SetBgControl_candidate(3, g_dwStartupBg3Control);
    bgCtrl2 = g_dwStartupBg2Control;
    SetBgControl_candidate(2, bgCtrl2);
    SetBgControl_candidate(1, g_dwStartupBg1Control);

    LoadBgGraphic_candidate(3, g_StartupBg3Graphic, 1, 0, 0, 0);
    ClearBgTilemap_candidate(2);
    LoadBgGraphic_candidate(2, g_StartupBg2Graphic, 1, 0, 0, 0);
    ClearBgTilemap_candidate(1);

    SetTextTargetFromBgControl_candidate(bgCtrl2);
    SelectTextFont_candidate(3, 0, 0);
    pText = GetDialogText(0xA47);  // "Challenge Everything™"
    cursor = DrawTextLines_candidate(0xA0, 0x78, 0x70, 0xD2, 0x10, &pText, 1);
    SelectTextFont_candidate(1, 0, 0);
    pText = GetDialogText(0xA48);  // "EA GAMES™ is an Electronic Arts™ Brand."
    DrawTextLines_candidate(cursor, 0x78, 0x80, 0xE0, 0x10, &pText, 1);

    if (g_PrevGameModeCtx.dwCurrentGameMode == 0)
        PlayScreenTransitionInByIndex_candidate(0x3F, 1);
    else
        PlayScreenTransitionInByIndex_candidate(0x3F, 2);

    g_GameModeStackContext.dwModeTimer_candidate = 0;
    g_GameModeStackContext.dwModeState_candidate = 0;
    PlayMusicModule(0x21);
}

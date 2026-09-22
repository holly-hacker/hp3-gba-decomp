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

    ResetDisplayState(0);
    SetBgControl(3, g_dwStartupBg3Control);
    bgCtrl2 = g_dwStartupBg2Control;
    SetBgControl(2, bgCtrl2);
    SetBgControl(1, g_dwStartupBg1Control);

    LoadBgGraphic(3, g_StartupBg3Graphic, 1, 0, 0, 0);
    ClearBgTilemap(2);
    LoadBgGraphic(2, g_StartupBg2Graphic, 1, 0, 0, 0);
    ClearBgTilemap(1);

    SetTextTargetFromBgControl(bgCtrl2);
    SelectTextFont(3, 0, 0);
    pText = GetDialogText(0xA47);  // "Challenge Everything™"
    cursor = DrawTextLines(0xA0, 0x78, 0x70, 0xD2, 0x10, &pText, 1);
    SelectTextFont(1, 0, 0);
    pText = GetDialogText(0xA48);  // "EA GAMES™ is an Electronic Arts™ Brand."
    DrawTextLines(cursor, 0x78, 0x80, 0xE0, 0x10, &pText, 1);

    if (g_PrevGameModeStackContext.dwCurrentGameMode == 0)
        PlayScreenTransitionInByIndex(0x3F, 1);
    else
        PlayScreenTransitionInByIndex(0x3F, 2);

    g_GameModeStackContext.dwModeTimer = 0;
    g_GameModeStackContext.dwModeState = 0;
    PlayMusicModule(0x21);
}

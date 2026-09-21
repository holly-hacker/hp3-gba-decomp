#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "text.h"

void UpdateStartup(void)
{
    u8 *pText;

    g_GameModeStackContext.dwModeTimer++;
    g_GameModeStackContext.dwModeSubState += 2;

    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
        if (g_GameModeStackContext.dwModeTimer == 0x84)
        {
            SetAlphaBlendCoefficients(0x10, 0);
            SetAlphaBlendTargets(6, 8);
            g_GameModeStackContext.dwModeSubState = 0;
            g_GameModeStackContext.dwModeState = 1;
        }
        break;

    case 1:
        SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                                  g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            ClearBgTilemap_candidate(2);
            ClearBgTilemap_candidate(1);
            LoadBgGraphic_candidate(2, g_StartupNoticeGraphic, 1, 0, 8, 1);
            SetTextTargetFromBgControl_candidate(g_dwStartupBg1Control);
            SelectTextFont_candidate(8, 0, -1);
            pText = GetDialogText(0x8E5);  // Harry Potter / WBIE trademark and copyright notice
            DrawTextLines_candidate(0xE0, 0x78, 0x67, 0xE0, 0x50, &pText, 1);
            g_GameModeStackContext.dwModeState = 2;
            g_GameModeStackContext.dwModeSubState = 0;
        }
        break;

    case 2:
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  0x10 - g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            g_GameModeStackContext.dwModeTimer = 0;
            g_GameModeStackContext.dwModeState = 3;
        }
        break;

    case 3:
        if (g_GameModeStackContext.dwModeTimer == 0x84)
        {
            // French shows the English notice after its translation.
            if (GetLanguage() == LanguageFrench)
            {
                g_GameModeStackContext.dwModeTimer = 0;
                g_GameModeStackContext.dwModeState = 4;
                SetAlphaBlendTargets(2, 8);
                g_GameModeStackContext.dwModeSubState = 0;
            }
            else
                PushGameMode(MainMenu);
        }
        break;

    case 4:
        SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                                  g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            ClearBgTilemap_candidate(1);
            pText = GetDialogText(0x8E9);  // same notice, English text in every language
            DrawTextLines_candidate(0xE0, 0x78, 0x67, 0xE0, 0x50, &pText, 1);
            g_GameModeStackContext.dwModeState = 5;
            g_GameModeStackContext.dwModeSubState = 0;
        }
        break;

    case 5:
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  0x10 - g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            g_GameModeStackContext.dwModeTimer = 0;
            g_GameModeStackContext.dwModeState = 6;
        }
        break;

    case 6:
        if (g_GameModeStackContext.dwModeTimer == 0x84)
            PushGameMode(MainMenu);
        break;
    }
}

#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "input.h"
#include "main_menu.h"
#include "mt19937.h"
#include "text.h"

void UpdateMainMenu(void)
{
    u32 timeout;
    u8 *pText;

    timeout = g_adwMainMenuStateTimeouts[g_GameModeStackContext.dwModeState];
    if (timeout != 0)
    {
        g_GameModeStackContext.dwModeTimer++;
        if (g_GameModeStackContext.dwModeTimer < timeout)
            return;
    }

    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  0x10 - g_GameModeStackContext.dwModeSubState);
        g_GameModeStackContext.dwModeSubState++;
        if (g_GameModeStackContext.dwModeSubState > 0x10)
        {
            SetAlphaBlendTargets(2, 0xC);
            SetAlphaBlendCoefficients(0, 0x10);
            g_GameModeStackContext.dwModeSubState = 0;
            EnableBg(1);
            if (g_PrevGameModeCtx.dwCurrentGameMode == Startup)
            {
                DrawMainMenuCopyright_candidate();
                g_GameModeStackContext.dwModeState = 3;
            }
            else
            {
                ShowMainMenuEntries_candidate();
                g_GameModeStackContext.dwModeState = 1;
            }
        }
        break;

    case 1:
        g_GameModeStackContext.dwModeSubState += 2;
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  0x10 - g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState > 0xF)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & (KeyA | KeyStart))
            SelectMainMenuEntry_candidate();
        else if (g_wKeysPressed & (KeyUp | KeyDown))
            MoveMainMenuCursor_candidate();
        break;

    case 3:
        g_GameModeStackContext.dwModeSubState += 2;
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  0x10 - g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState > 0xF)
        {
            g_GameModeStackContext.dwModeState = 4;
            g_GameModeStackContext.dwModeTimer = 0;
        }
        break;

    case 4:
        if (g_GameModeStackContext.dwModeTimer <= 0x3B)
        {
            g_GameModeStackContext.dwModeTimer++;
            if (g_GameModeStackContext.dwModeTimer == 0x3C)
            {
                SelectTextFont_candidate(2, 6, -1);
                pText = GetDialogText(0x8E8);  // "Press START"
                DrawTextLines_candidate(g_dwMainMenuTextCursor, 0x78, 0x8D, 0xB4, 0x10, &pText, 1);
            }
        }
        else if (g_wKeysPressed & KeyStart)
        {
            // Seeds the RNG. This reads the active keys and will always include START as a key.
            Mt19937AutoSeed();
            PlaySoundById(1);
            g_GameModeStackContext.dwModeState = 5;
            g_GameModeStackContext.dwModeSubState = 0x10;
        }
        break;

    case 5:
        g_GameModeStackContext.dwModeSubState -= 2;
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  0x10 - g_GameModeStackContext.dwModeSubState);
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            ClearBgTilemap_candidate(1);
            ShowMainMenuEntries_candidate();
            g_GameModeStackContext.dwModeState = 1;
        }
        break;
    }
}

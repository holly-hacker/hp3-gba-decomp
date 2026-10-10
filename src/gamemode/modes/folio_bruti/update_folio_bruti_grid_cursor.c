#include "types.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "input.h"
#include "menu/folio_bruti.h"
#include "menu/minigame_menu.h"

void UpdateFolioBrutiGridCursor(void)
{
    if (g_wKeysPressed & (KeyRight | KeyLeft | KeyUp | KeyDown))
    {
        PlaySoundById(0);

        // The cell in the bottom right corner is unused and skipped over.
        if (g_wKeysPressed & KeyLeft)
        {
            do
            {
                g_FolioBrutiState.dwColumn--;
                if ((s32)g_FolioBrutiState.dwColumn < 0)
                {
                    g_FolioBrutiState.dwColumn = 8;
                    g_FolioBrutiState.dwRow--;
                    if ((s32)g_FolioBrutiState.dwRow < 0)
                        g_FolioBrutiState.dwRow = 5;
                }
            } while (g_FolioBrutiState.dwColumn == 8 && g_FolioBrutiState.dwRow == 5);
        }
        else if (g_wKeysPressed & KeyRight)
        {
            do
            {
                g_FolioBrutiState.dwColumn++;
                if ((s32)g_FolioBrutiState.dwColumn > 8)
                {
                    g_FolioBrutiState.dwColumn = 0;
                    g_FolioBrutiState.dwRow++;
                    if ((s32)g_FolioBrutiState.dwRow > 5)
                        g_FolioBrutiState.dwRow = 0;
                }
            } while (g_FolioBrutiState.dwColumn == 8 && g_FolioBrutiState.dwRow == 5);
        }
        else if (g_wKeysPressed & KeyUp)
        {
            do
            {
                if (g_FolioBrutiState.dwRow == 0)
                    g_FolioBrutiState.dwRow = 5;
                else
                    g_FolioBrutiState.dwRow--;
            } while (g_FolioBrutiState.dwColumn == 8 && g_FolioBrutiState.dwRow == 5);
        }
        else if (g_wKeysPressed & KeyDown)
        {
            do
            {
                if (g_FolioBrutiState.dwRow == 5)
                    g_FolioBrutiState.dwRow = 0;
                else
                    g_FolioBrutiState.dwRow++;
            } while (g_FolioBrutiState.dwColumn == 8 && g_FolioBrutiState.dwRow == 5);
        }

        SetObjectMoveTargetWithDuration_candidate(g_FolioBrutiState.pCursor, (g_FolioBrutiState.dwColumn + 3) * 8,
                                                  (g_FolioBrutiState.dwRow + 3) * 8, 5);
        DrawFolioBrutiMonsterPanel();
    }

    if ((g_wKeysPressed & KeyA) || (g_wKeysPressed & KeyB))
    {
        PlaySoundById(2);
        if (g_PrevGameModeStackContext.dwCurrentGameMode != Battle)
        {
            PushGameMode_2(Folios, 1, 0);
        }
        else
        {
            g_GameModeStackContext.dwCurrentGameModeArg2 = 0xFF;
            PushGameMode_3(Battle, g_PrevGameModeStackContext.dwCurrentGameModeArg1,
                           g_PrevGameModeStackContext.dwCurrentGameModeArg2,
                           g_PrevGameModeStackContext.dwCurrentGameModeArg3);
        }
    }
}

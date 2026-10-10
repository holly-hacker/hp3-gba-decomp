#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "graphics/text.h"
#include "game/game_modes.h"
#include "input.h"
#include "hw/mem.h"
#include "overworld/room.h"
#include "battle/effect_script.h"
#include "battle/victory_screen.h"

void UpdateVictoryScreen(void)
{
    u8 *pText;

    switch (g_GameModeStackContext.dwModeState)
    {
    case VictoryStateIntroDelay:
        g_GameModeStackContext.dwModeTimer--;
        if (g_GameModeStackContext.dwModeTimer == -1)
            g_GameModeStackContext.dwModeState = VictoryStateXp;
        break;

    case VictoryStateXp:
        if (g_dwVictoryXpRemaining != 0)
        {
            if (g_dwVictoryXpRemaining & 1)
                PlaySoundById(0x1A);

            sub_08014004();
            if (g_wKeysPressed & KeyA)
            {
                while (g_dwVictoryXpRemaining != 0)
                    sub_08014004();
            }

            if (g_dwVictoryXpRemaining != 0)
                break;

            g_GameModeStackContext.dwModeTimer = 0x3C;
            g_GameModeStackContext.dwModeState = VictoryStateIntroDelay;
            g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
            break;
        }

        if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0)
        {
            g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
            ClearBgTilemapRect(0, 0, 0x12, 0x1E, 2);
            SelectTextFont(1, 0, -1);
            pText = GetDialogText(0x647);  // "Press the A Button to continue."
            g_wVictoryTextTileCursor = DrawStringAligned(g_wVictoryTextTileCursor, 0x78, 0x94, pText, 1);
        }

        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            SetAlphaBlendTargets(0x17, 0xC);
            SetAlphaBlendCoefficients(0xF, 0);
            g_GameModeStackContext.dwModeState = VictoryStateFadeOutXp;
            g_GameModeStackContext.dwModeTimer = 0x10;
        }
        break;

    case VictoryStateFadeOutXp:
        if (g_GameModeStackContext.dwModeTimer-- > 0)
        {
            SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeTimer, 0x10 - g_GameModeStackContext.dwModeTimer);
            if (g_GameModeStackContext.dwModeTimer == 2)
                ClearBgTilemap(0);
        }
        else
        {
            ClearBgTilemap(1);
            ClearBgTilemap(2);
            FreeAllObjects(&g_ActiveObjectListState.pHead);
            sub_0801456C();
            SetAlphaBlendTargets(0x11, 8);
            SetAlphaBlendCoefficients(0, 0x10);
            g_GameModeStackContext.dwModeState = VictoryStateFadeInDrops;
            g_GameModeStackContext.dwModeTimer = 0x10;
        }
        break;

    case VictoryStateFadeInDrops:
        if (g_GameModeStackContext.dwModeTimer != 0)
        {
            g_GameModeStackContext.dwModeTimer--;
            SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeTimer, g_GameModeStackContext.dwModeTimer);
        }
        else
            g_GameModeStackContext.dwModeState = VictoryStateDrops;
        break;

    case VictoryStateDrops:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            PushGameMode_2(Overworld, 2, g_bCurrentRoomId);
        }
        break;
    }
}

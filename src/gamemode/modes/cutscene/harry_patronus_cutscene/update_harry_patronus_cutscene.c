#include "types.h"
#include "battle.h"
#include "display.h"
#include "divination_tea.h"
#include "game_modes.h"
#include "harry_patronus_cutscene.h"
#include "input.h"
#include "room_script.h"

// Every fourth frame the next graphic is loaded into the back BG and swapped in. The state machine
// fades in from black, runs until frame 0xF0 or a key press, fades to white, then leaves for the
// overworld: with arg1 == 1 in the current room, otherwise by exit 0x21.
void UpdateHarryPatronusCutscene(void)
{
    u32 frame;
    u32 bg;

    g_swPatronusBgParam--;
    g_nPatronusBgOffset += 0x6666;
    frame = g_GameModeStackContext.dwCurrentGameModeArg2 & 3;
    g_GameModeStackContext.dwCurrentGameModeArg2++;

    if (frame == 3 && g_dwPatronusSwapPending == 0)
    {
        g_bPatronusGraphicIndex++;
        if (g_bPatronusGraphicIndex > 5)
            g_bPatronusGraphicIndex = 0;
        LoadBgGraphic(g_dwPatronusBgBack, g_apPatronusGraphics[g_bPatronusGraphicIndex], 0, 0, 0, 0);
        bg = g_dwPatronusBgBack;
        g_dwPatronusBgBack = g_dwPatronusBgFront;
        g_dwPatronusBgFront = bg;
        g_dwPatronusSwapPending = 1;
    }

    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
        g_GameModeStackContext.dwCurrentGameModeArg3 = 0x10;
        g_GameModeStackContext.dwModeState = 1;
        break;
    case 1:
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0)
            g_GameModeStackContext.dwModeState = 2;
        SetFadeToBlack(0x3F, g_GameModeStackContext.dwCurrentGameModeArg3);
        g_GameModeStackContext.dwCurrentGameModeArg3--;
        break;
    case 2:
        if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0xF0
            || (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwCurrentGameModeArg3 = 0;
            g_GameModeStackContext.dwModeState = 3;
        }
        break;
    case 3:
        if (g_GameModeStackContext.dwCurrentGameModeArg3 > 0xF)
        {
            g_GameModeStackContext.dwModeState = 4;
            g_GameModeStackContext.dwCurrentGameModeArg3 = 0x10;
        }
        SetFadeToWhite(0x3F, g_GameModeStackContext.dwCurrentGameModeArg3);
        g_GameModeStackContext.dwCurrentGameModeArg3++;
        break;
    case 4:
    default:
        if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
        {
            PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
            g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
            g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
        }
        else
        {
            g_abRoomScriptExitParams_candidate[0] = 2;
            PushGameMode_2(Overworld, 0, 0x21);
        }
        break;
    }
}

#include "types.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"
#include "mt19937.h"
#include "object.h"
#include "room.h"
#include "room_script.h"

void UpdateDebugMapSelectMenu(void)
{
    s32 mapIndex;

    mapIndex = (g_DebugMapSelectState.nScrollY / 8 + (s32)g_DebugMapSelectState.dwCursorRow) % 64;

    if (--g_GameModeStackContext.dwModeTimer == -1)
    {
        g_GameModeStackContext.dwModeTimer = 2;

        if ((g_wKeysHeld & KeyDown) && g_DebugMapSelectState.dwCursorRow == 0x11 && mapIndex <= 0x35)
        {
            sub_0800B158(0);
        }
        else if ((g_wKeysHeld & KeyUp) && g_DebugMapSelectState.dwCursorRow == 0 && mapIndex > 0)
        {
            sub_0800B158(1);
        }
        else if (g_wKeysHeld & KeyLeft)
        {
            g_DebugMapSelectState.nScrollY -= 0x88;
            if (g_DebugMapSelectState.nScrollY < 0)
            {
                g_DebugMapSelectState.nScrollY = 0;
                g_DebugMapSelectState.dwCursorRow = 0;
            }
            sub_08007AF0(1, 0, g_DebugMapSelectState.nScrollY << 16);
        }
        else if (g_wKeysHeld & KeyRight)
        {
            g_DebugMapSelectState.nScrollY += 0x88;
            sub_08007AF0(1, 0, g_DebugMapSelectState.nScrollY << 16);
        }

        if (sub_08025A18(&g_DebugMapSelectState.dwCursorRow, 0, 0x11, 0, 0))
            SetObjectPosition(g_DebugMapSelectState.pCursorObject, 0x78, g_DebugMapSelectState.dwCursorRow * 8 + 0xB);
    }

    if (g_wKeysPressed & KeyA)
    {
        g_abRoomScriptExitParams_candidate[0] = 0;
        g_abQuestEventState[0xFE] = 0;
        Mt19937AutoSeed();
        PushGameMode_2(Overworld, 0, mapIndex);
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
    else if (g_wKeysPressed & KeySelect)
    {
        PushGameMode_2(Overworld, 0, 0x35);
    }
}

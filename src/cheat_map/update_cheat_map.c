#include "types.h"
#include "background.h"
#include "cheat_map.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "input.h"
#include "menu/minigame_menu.h"
#include "mt19937.h"
#include "actor.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

void UpdateCheatMap(void)
{
    s32 mapIndex;

    mapIndex = (g_CheatMapState.nScrollY / 8 + (s32)g_CheatMapState.dwCursorRow) % 64;

    if (--g_GameModeStackContext.dwModeTimer == -1)
    {
        g_GameModeStackContext.dwModeTimer = 2;

        if ((g_wKeysHeld & KeyDown) && g_CheatMapState.dwCursorRow == 0x11 && mapIndex <= 0x35)
        {
            sub_0800B158(0);
        }
        else if ((g_wKeysHeld & KeyUp) && g_CheatMapState.dwCursorRow == 0 && mapIndex > 0)
        {
            sub_0800B158(1);
        }
        else if (g_wKeysHeld & KeyLeft)
        {
            g_CheatMapState.nScrollY -= 0x88;
            if (g_CheatMapState.nScrollY < 0)
            {
                g_CheatMapState.nScrollY = 0;
                g_CheatMapState.dwCursorRow = 0;
            }
            SetBgScrollFixed(1, 0, g_CheatMapState.nScrollY << 16);
        }
        else if (g_wKeysHeld & KeyRight)
        {
            g_CheatMapState.nScrollY += 0x88;
            SetBgScrollFixed(1, 0, g_CheatMapState.nScrollY << 16);
        }

        if (StepCursorUpDownHeld(&g_CheatMapState.dwCursorRow, 0, 0x11, 0, 0))
            SetActorPosition(g_CheatMapState.pCursorActor, 0x78, g_CheatMapState.dwCursorRow * 8 + 0xB);
    }

    if (g_wKeysPressed & KeyA)
    {
        g_abRoomScriptExitParams_candidate[0] = 0;
        g_abQuestEventState[QUEST_SPAWN_ID_COPY] = 0;
        Mt19937AutoSeed();
        PushGameMode_2(Overworld, 0, mapIndex);
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
    else if (g_wKeysPressed & KeySelect)
    {
        PushGameMode_2(Overworld, 0, 0x35);
    }
}

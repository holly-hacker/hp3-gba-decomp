#include "types.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "hw/input.h"
#include "menu/loading_screen.h"
#include "menu/main_menu.h"
#include "menu/minigame_menu.h"
#include "overworld/room.h"

void UpdateLoadingScreen(void)
{
    if (g_GameModeStackContext.dwModeTimer != 0)
    {
        g_GameModeStackContext.dwModeTimer--;
        return;
    }

    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (g_abLoadingScreenTwoOptions[g_LoadingScreenState.bStageRow] != 0)
    {
        if (StepWrappedSelectionHorizontal_candidate(&g_GameModeStackContext.dwCurrentGameModeArg2, 0, 1, 1, 0))
        {
            sub_0800C3FC();
            sub_0801DCC4(g_LoadingScreenState.pCursorObject,
                         g_GameModeStackContext.dwCurrentGameModeArg2 * 0x50 + 0x4D,
                         0x4E);
            PlaySoundById(0);
            return;
        }
    }
    else
    {
        if (StepWrappedSelectionHorizontal_candidate(&g_GameModeStackContext.dwCurrentGameModeArg2, 0, 2, 1, 0))
        {
            sub_0800C3FC();
            sub_0801DCC4(g_LoadingScreenState.pCursorObject,
                         g_GameModeStackContext.dwCurrentGameModeArg2 * 0x50 + 0x4D,
                         0x4E);
            PlaySoundById(0);
            return;
        }
    }

    if (g_LoadingScreenState.bInputDelay != 0)
    {
        g_LoadingScreenState.bInputDelay--;
    }
    else if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(4);
        g_dwGameModeFlags &= ~1;
        PushGameMode_2(g_PrevGameModeStackContext.dwCurrentGameMode, 9, g_bCurrentRoomId);

        g_abQuestEventState[0xFF] = g_GameModeStackContext.dwCurrentGameModeArg2;
        g_LoadingScreenState.bPreviousStage = g_abQuestEventState[0];
        switch (g_GameModeStackContext.dwCurrentGameModeArg2)
        {
        case 0:
            g_abQuestEventState[0] = g_LoadingScreenState.abOptionStage[0];
            break;
        case 1:
            g_abQuestEventState[0] = g_LoadingScreenState.abOptionStage[1];
            break;
        case 2:
            g_abQuestEventState[0] = g_LoadingScreenState.abOptionStage[2];
            break;
        }
    }
}

#include "types.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "overworld/room.h"
#include "dementor_minigame.h"

void LeaveDementorMinigame(void)
{
    if (g_dwDementorMinigameScriptFlag_candidate != 0)
    {
        PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
        g_dwPendingGameMode.dwCurrentGameModeArg1 = 3;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
        UnmuteAllMusicChannels();
    }
    else
    {
        PushGameMode_2(MinigameDifficultySelect, 5, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}

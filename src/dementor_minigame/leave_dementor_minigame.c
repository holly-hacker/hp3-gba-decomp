#include "types.h"
#include "modes.h"
#include "sound.h"
#include "overworld/room.h"
#include "dementor_minigame.h"
#include "map.h"

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

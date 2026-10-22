#include "modes.h"
#include "sound.h"
#include "dementor_minigame.h"
#include "map.h"

void LeaveDementorMinigame(void)
{
    if (g_dwDementorMinigameScriptFlag_candidate != 0)
    {
        PushGameMode_2(Overworld, OverworldEntryEnterRoom, g_bCurrentRoomId);
        g_dwPendingGameMode.dwCurrentGameModeArg1 = OverworldEntryReturn;
        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0xFF;
        StopSoundEffectChannels();
    }
    else
    {
        PushGameMode_2(MinigameDifficultySelect, 5, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}

#include "modes.h"
#include "sound.h"
#include "buckbeak_minigame.h"
#include "hero.h"
#include "map.h"

void HandleBuckbeakMinigameExitSelect(void)
{
    if (g_dwBuckbeakMinigameForceOverworldExit != 0)
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 2)
        {
            g_abRoomScriptExitParams_candidate[0] = 0;
            PushGameMode_2(Overworld, OverworldEntryEnterRoom, 0x19);
            StopSoundEffectChannels();
        }
        else
        {
            PushGameMode_2(Overworld, OverworldEntryEnterRoom, g_bCurrentRoomId);
            StopSoundEffectChannels();
        }
    }
    else
        PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);
}

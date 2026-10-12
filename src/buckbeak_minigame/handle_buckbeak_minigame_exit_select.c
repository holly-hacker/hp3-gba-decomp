#include "types.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "overworld/room.h"
#include "overworld/room_script.h"
#include "buckbeak_minigame.h"

void HandleBuckbeakMinigameExitSelect(void)
{
    if (g_dwBuckbeakMinigameForceOverworldExit != 0)
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 2)
        {
            g_abRoomScriptExitParams_candidate[0] = 0;
            PushGameMode_2(Overworld, 0, 0x19);
            UnmuteAllMusicChannels();
        }
        else
        {
            PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
            UnmuteAllMusicChannels();
        }
    }
    else
        PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);
}

#include "modes.h"
#include "boggart_minigame.h"
#include "map.h"

void LeaveBoggartMinigame(void)
{
    if (g_dwBoggartMinigameScriptFlag_candidate != 0)
    {
        PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
        g_BoggartMinigame.dwExitToMenu = 1;
    }
    else
    {
        PushGameMode_2(MinigameDifficultySelect, 5, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}

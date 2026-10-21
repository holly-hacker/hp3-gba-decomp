#include "types.h"
#include "map.h"
#include "modes.h"
#include "sound.h"
#include "pop_it_minigame.h"

void QuitWizardCrackerPopItMinigame(void)
{
    if (g_dwWizardCrackerPopItForceOverworldExit != 0)
    {
        PushGameMode_2(Overworld, 0, g_bCurrentRoomId);
        StopSoundEffectChannels();
    }
    else
    {
        PushGameMode_2(MinigameDifficultySelect, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}

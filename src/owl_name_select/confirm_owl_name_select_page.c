#include "types.h"
#include "modes.h"
#include "sound.h"
#include "screen_transitions.h"
#include "owl_name_select.h"

void ConfirmOwlNameSelectPage(void)
{
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
    {
        SetAlphaBlendTargets(4, 0xB);
        g_GameModeStackContext.dwModeState = 4;
        g_GameModeStackContext.dwModeScratchA = 0;
    }
    else
        PushGameMode_2(OwlCareMinigame, 5, 0);
    PlaySoundById(1);
}

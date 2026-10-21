#include "types.h"
#include "modes.h"
#include "sound.h"
#include "screen_transitions.h"
#include "owl_name_select.h"

void CancelOwlNameSelectPage(void)
{
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
        SetAlphaBlendTargets(0x14, 0xB);
    g_GameModeStackContext.dwModeState = 4;
    g_GameModeStackContext.dwModeScratchA = 1;
    PlaySoundById(2);
}

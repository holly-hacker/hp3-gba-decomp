#include "types.h"
#include "actor.h"
#include "modes.h"
#include "sound.h"
#include "hedwig_minigame.h"

// B button: back to the Connectivity menu, unless the owl is flying out or in.
void HandleOwlCareKitCancel(void)
{
    Actor *pOwl = g_OwlCareKitScreen.pOwl;

    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (pOwl->bActionState != OwlStateMailDepart && pOwl->bActionState != OwlStateMailReturn)
    {
        PlaySoundById(2);
        PushGameMode_2(Connectivity, 1, 0);
    }
    else
        PlaySoundById(3);
}

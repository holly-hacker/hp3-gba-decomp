#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "cutscene/harry_patronus_cutscene.h"
#include "actor.h"

void HandleHarryPatronusCutsceneVBlank(void)
{
    CommitQueuedActorTileUpdates();
    SetBgRotationCenter(2, g_nPatronusBgOffset >> 16, 0);
    SetBgRotationCenter(3, g_nPatronusBgOffset >> 16, 0);
    SetBgZoom(2, g_swPatronusBgParam);
    SetBgZoom(3, g_swPatronusBgParam);

    if (g_dwPatronusSwapPending != 0)
    {
        EnableBg(g_dwPatronusBgFront);
        DisableBg(g_dwPatronusBgBack);
        g_dwPatronusSwapPending = 0;
    }
}

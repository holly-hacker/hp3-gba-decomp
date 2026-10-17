#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "cutscene.h"
#include "screen_transitions.h"

void ExitLinearCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetBgScrollStep(1, 0, 0);

    if (g_pLinearCutsceneActor != NULL)
    {
        FreeActor(g_pLinearCutsceneActor);
        g_pLinearCutsceneActor = NULL;
    }
}

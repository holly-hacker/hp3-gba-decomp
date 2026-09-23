#include "types.h"
#include "display.h"
#include "linear_cutscene.h"
#include "mem.h"
#include "wizard_cracker_pop_it.h"

void ExitLinearCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_08007D14(1, 0, 0);

    if (g_pLinearCutsceneObject != NULL)
    {
        FreeObject(g_pLinearCutsceneObject);
        g_pLinearCutsceneObject = NULL;
    }
}

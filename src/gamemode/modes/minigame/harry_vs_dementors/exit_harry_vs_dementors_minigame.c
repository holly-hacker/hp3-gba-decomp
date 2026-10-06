#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "minigame/harry_vs_dementors.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "menu/minigame_menu.h"

void ExitHarryVsDementorsMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_HarryVsDementors.pCursorObject != NULL)
    {
        ReleaseMenuCursor(g_HarryVsDementors.pCursorObject);
        g_HarryVsDementors.pCursorObject = NULL;
        FreeAllParticles();
    }

    sub_0802CEE4(g_HarryVsDementors.pObjectGroup20);
    sub_0802CEE4(g_HarryVsDementors.pObjectGroup24);
    sub_0802CEE4(g_HarryVsDementors.pObjectGroup28);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0803FF04();
}

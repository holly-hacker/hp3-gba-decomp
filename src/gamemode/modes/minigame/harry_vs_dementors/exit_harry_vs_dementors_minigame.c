#include "types.h"
#include "battle.h"
#include "display.h"
#include "harry_vs_dementors.h"
#include "main_menu.h"
#include "mem.h"
#include "minigame_menu.h"

void ExitHarryVsDementorsMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);

    if (g_HarryVsDementors.pCursorObject != NULL)
    {
        sub_0801DC6C(g_HarryVsDementors.pCursorObject);
        g_HarryVsDementors.pCursorObject = NULL;
        sub_0803171C();
    }

    sub_0802CEE4(g_HarryVsDementors.pObjectGroup20);
    sub_0802CEE4(g_HarryVsDementors.pObjectGroup24);
    sub_0802CEE4(g_HarryVsDementors.pObjectGroup28);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0803FF04();
}

#include "types.h"
#include "battle.h"
#include "display.h"
#include "divination_tea.h"
#include "main_menu.h"
#include "mem.h"

void ExitDivinationTeaMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);

    if (g_DivinationTea.pCursorObject != NULL)
    {
        sub_0801DC6C(g_DivinationTea.pCursorObject);
        g_DivinationTea.pCursorObject = NULL;
        sub_080316D4();
        sub_0803171C();
    }

    sub_0800D2DC();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0800A914();
}

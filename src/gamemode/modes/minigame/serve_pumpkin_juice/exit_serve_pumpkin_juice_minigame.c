#include "types.h"
#include "battle.h"
#include "display.h"
#include "mem.h"
#include "minigame_menu.h"

void ExitUnusedServePumpkinJuiceMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    sub_0800D2DC();
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_0803FF04();
    sub_0800A914();
}

#include "types.h"
#include "display.h"
#include "mem.h"
#include "minigame_menu.h"

void ExitDebugSoundTestMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0803FF04();
    sub_080015D4(&g_ActiveObjectListState.pHead);
}

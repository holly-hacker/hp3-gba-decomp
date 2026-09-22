#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_save.h"
#include "main_menu.h"
#include "mem.h"

void ExitGameSave(void)
{
    sub_0803D420(0, 8);
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0803D420(0, 8);
    sub_0801E0DC();
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_0800D2DC();
}

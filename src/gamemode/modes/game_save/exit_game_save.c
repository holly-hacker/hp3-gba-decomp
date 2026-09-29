#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_save.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

void ExitGameSave(void)
{
    sub_0803D420(0, 8);
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0803D420(0, 8);
    sub_0801E0DC();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0800D2DC();
}

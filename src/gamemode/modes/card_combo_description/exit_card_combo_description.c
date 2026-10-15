#include "types.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "actor.h"
#include "menu/main_menu.h"

void ExitCardComboDescription(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
}

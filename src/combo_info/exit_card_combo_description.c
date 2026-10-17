#include "types.h"
#include "combo_info.h"
#include "mem.h"
#include "actor.h"
#include "default_menu.h"
#include "screen_transitions.h"

void ExitCardComboDescription(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
}

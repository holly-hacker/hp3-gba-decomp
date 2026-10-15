#include "types.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "actor.h"

void ExitPurpleScreenReturnToMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}

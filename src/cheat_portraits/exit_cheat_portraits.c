#include "types.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"

void ExitCheatPortraits(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}

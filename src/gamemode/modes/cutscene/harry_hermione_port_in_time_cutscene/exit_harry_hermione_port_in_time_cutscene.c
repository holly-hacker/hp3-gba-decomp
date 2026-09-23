#include "types.h"
#include "display.h"
#include "mem.h"
#include "overworld.h"
#include "room.h"

void ExitHarryHermionePortInTimeCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0802DDAC();
    sub_0803EA3C();
}

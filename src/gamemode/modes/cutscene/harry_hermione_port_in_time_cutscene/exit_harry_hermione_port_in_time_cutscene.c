#include "types.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void ExitHarryHermionePortInTimeCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0802DDAC();
    sub_0803EA3C();
}

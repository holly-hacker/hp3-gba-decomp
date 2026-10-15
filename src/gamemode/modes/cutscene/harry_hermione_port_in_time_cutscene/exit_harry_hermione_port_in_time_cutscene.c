#include "types.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void ExitHarryHermionePortInTimeCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeRoomSharedTileset();
    sub_0803EA3C();
}

#include "types.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "move.h"
#include "screen_transitions.h"
#include "scroll.h"
#include "time_turner_cutscene.h"

void ExitHarryHermionePortInTimeCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeRoomSharedTileset();
    sub_0803EA3C();
}

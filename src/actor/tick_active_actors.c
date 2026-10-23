#include "types.h"
#include "actor.h"

// Ticks the active actor list with the full per-frame pass (mode 1) and
// returns TickActorList's OAM-work result, which both callers discard.
u32 TickActiveActors(void)
{
    g_dwActorListTicked = 1;
    return TickActorList(&g_ActiveActorListState, 1);
}

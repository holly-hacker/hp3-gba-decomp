#include "types.h"
#include "object.h"
#include "mem.h"

// Ticks the active object list with the full per-frame pass (mode 1) and
// returns TickObjectList's OAM-work result, which both callers discard.
u32 TickActiveObjects(void)
{
    g_dwObjectListTicked_candidate = 1;
    return TickObjectList(&g_ActiveObjectListState, 1);
}

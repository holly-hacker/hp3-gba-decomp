#include "types.h"
#include "object.h"
#include "mem.h"

// Sets `flags` on every object on the active list. Unused.
void SetActiveObjectsFlags(ObjectFlags flags)
{
    ListNode *node;

    for (node = g_ActiveObjectListState.pHead; node != NULL; node = node->pNext)
        ((Object *)node)->dwFlags |= flags;
}

// Clears `flags` on every object on the active list. Unused.
void ClearActiveObjectsFlags(ObjectFlags flags)
{
    ListNode *node;

    for (node = g_ActiveObjectListState.pHead; node != NULL; node = node->pNext)
        ((Object *)node)->dwFlags &= ~flags;
}

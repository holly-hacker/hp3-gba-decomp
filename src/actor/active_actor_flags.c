#include "actor.h"

// Sets `flags` on every actor on the active list. Unused.
void SetActiveActorsFlags(ActorFlags flags)
{
    ListNode *node;

    for (node = g_ActiveActorListState.pHead; node != NULL; node = node->pNext)
        ((Actor *)node)->dwFlags |= flags;
}

// Clears `flags` on every actor on the active list. Unused.
void ClearActiveActorsFlags(ActorFlags flags)
{
    ListNode *node;

    for (node = g_ActiveActorListState.pHead; node != NULL; node = node->pNext)
        ((Actor *)node)->dwFlags &= ~flags;
}

#include "mem.h"

// Pops a node off freeListHead, zeroes it, pushes it onto
// activeListHead, and returns it (NULL if freeListHead was empty).
// Called by AllocDefaultObject/SpawnObject against g_ObjectPoolState's
// free list and g_ActiveObjectListState's active list.
void *AllocObjectFromFreeList(ListNode **freeListHead, ListNode **activeListHead, u32 size)
{
    ListNode *obj;

    if (*freeListHead == NULL) {
        return NULL;
    }

    obj = List_PopHead(freeListHead);
    memset(obj, 0, size);
    List_PushHead(activeListHead, obj);
    return obj;
}

#include "object.h"
#include "mem.h"

// Pops an object off the free list and resets its default sentinel fields
// (no type, no room-tile binding, no VRAM tile allocation).
Object *AllocDefaultObject(void)
{
    Object *obj = (Object *)AllocObjectFromFreeList(
        (ListNode **)&g_ObjectPoolState.pFreeListHead,
        &g_ActiveObjectListState.pHead, sizeof(Object));

    if (g_ActiveObjectListState.pUnk4 == NULL) {
        g_ActiveObjectListState.pUnk4 = (ListNode *)obj;
    }
    obj->wFlags_0xAC |= 1;
    obj->wObjectType = 0xFFFF;
    obj->wVramTileAllocId = 0xFFFF;
    obj->bRoomTileCol_candidate = 0xFF;
    obj->bRoomTileRow_candidate = 0xFF;
    return obj;
}

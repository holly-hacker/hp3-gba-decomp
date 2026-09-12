#include "types.h"
#include "object.h"
#include "mem.h"

// Releases obj back to the object pool's free list; a no-op if it was
// already freed (wObjectType == 0xFFFF is the freed sentinel).
void FreeObject(Object *obj)
{
    u32 affineSlotState;

    if (obj->wObjectType == 0xFFFF)
        return;

    if (obj->pfnDestructor)
        obj->pfnDestructor(obj);

    ClaimObjectEffectResource(obj);

    if (obj->dwFlags & ObjectFlagRoomRecordBound)
        SetRoomObjectRecordPtr_candidate(0, obj->bRoomTileCol_candidate, obj->bRoomTileRow_candidate);

    obj->wObjectType = 0xFFFF;

    affineSlotState = ((u32)obj->bFlags_0xD1 << 30) >> 30;
    if (affineSlotState == 1 || affineSlotState == 3)
        ReleaseObjectAffineSlot(obj);

    if (g_dwUnk03001DC0 == 1)
        ReleaseObjectOffscreenVramTiles(obj);

    if (g_ActiveObjectListState.pUnk4 == (ListNode *)obj)
        g_ActiveObjectListState.pUnk4 = obj->node.pPrev;

    List_MoveToHead((ListNode **)&g_ObjectPoolState.pFreeListHead, &g_ActiveObjectListState.pHead, (ListNode *)obj);
}

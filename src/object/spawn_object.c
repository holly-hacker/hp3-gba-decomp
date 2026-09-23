#include "types.h"
#include "object.h"
#include "mem.h"

// Same body as AllocDefaultObject, inlined here.
static inline Object *AllocDefaultObjectInline(void)
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

// Allocates an object of the given type at pixel position (x, y) with the
// standard visible/animated flags. pPalette, when present, is passed to
// AttachObjectPalette. Returns the new object.
Object *SpawnObject(u32 type, s32 x, s32 y, const ObjPalette *pPalette)
{
    Object *obj = AllocDefaultObjectInline();

    if (obj != NULL)
    {
        SnapObjectPosition(obj, x << 16, y << 16);
        obj->wObjectType = type;
        obj->dwFlags = ObjectFlagVisible | ObjectFlagHasTickLogic | ObjectFlagHasAnimation
            | ObjectFlagSuppressEffectBinding;
        obj->bDepthSortBias = 0x80;
        if (pPalette != NULL)
            AttachObjectPalette(obj, pPalette);
    }
    return obj;
}

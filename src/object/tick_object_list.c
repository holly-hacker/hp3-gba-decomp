#include "types.h"
#include "object.h"
#include "mem.h"
#include "game_modes.h"

// Runs one update pass over an object list. TickObject runs for every object
// (from the tail when the mode flags allow the full pass), then the objects
// TickObject queued are drawn: the sprite-frame queue, then the depth-sorted OAM
// queue, flushing each draw layer's particles as the sort crosses its boundary.
// Returns 1 if any object's OAM update reported work.
u32 TickObjectList(ActiveObjectListState *list, u8 mode)
{
    Object *obj;
    Object *next;
    u32 orbit;
    u32 posX;
    u32 posY;
    u32 oamResult;
    u32 queueIndex;
    u32 layer;
    u32 anyOamWork;
    void (*pfnCheckCollisions)(u32, Object **) = (void (*)(u32, Object **))g_pCheckObjectCollisionsIwram;
    void (*pfnSortObjects)(Object **, u32) = (void (*)(Object **, u32))g_pSortObjectsIwram;

    anyOamWork = 0;
    g_bSpriteFrameQueueCount = 0;
    g_dwOamQueueCount = 0;
    g_ObjectPoolState.bTileUpdateQueueCount = 0;
    g_dwCollisionQueueCount = 0;
    layer = 0;

    if ((g_dwGameModeFlags & 0x40008) == 8) {
        obj = (Object *)list->pHead;
        while (obj != NULL) {
            next = (Object *)obj->node.pNext;
            TickObject(obj, mode);
            obj = next;
        }
    }
    else {
        obj = (Object *)list->pUnk4;
        while (obj != NULL) {
            next = (Object *)obj->node.pPrev;
            TickObject(obj, mode);
            obj = next;
        }

        if (!(g_dwGameModeFlags & 0x800) && g_dwCollisionQueueCount != 0 &&
            list == &g_ActiveObjectListState)
            pfnCheckCollisions(g_dwCollisionQueueCount, g_apCollisionQueue);

        for (obj = (Object *)list->pHead; obj != NULL; obj = (Object *)obj->node.pNext) {
            orbit = obj->dwOrbitRadii;
            if (obj->pOwnerObject != NULL)
                sub_080034B8(obj);

            posX = obj->nXPrev;
            posY = obj->nYPrev;
            obj->nX = posX;
            obj->nY = posY;
            if (orbit != 0)
                ApplyObjectOrbitMotion(obj);
        }
    }

    if (mode == 1 && g_dwObjectListActive_candidate != 0 && g_dwOamQueueCount > 1)
        pfnSortObjects(g_apOamQueue, g_dwOamQueueCount);

    for (queueIndex = g_bSpriteFrameQueueCount; queueIndex != 0; queueIndex--) {
        obj = g_apSpriteFrameQueue[queueIndex - 1];
        if (!(obj->dwFlags & ObjectFlagSkipSpriteFrameUpdate))
            UpdateObjectSpriteFrame(obj, mode);

        if (mode == 1) {
            oamResult = UpdateObjectOamCells(obj);
            if (oamResult != 0) {
                anyOamWork = 1;
                if (oamResult == 2)
                    g_ObjectPoolState.apTileUpdateQueue[g_ObjectPoolState.bTileUpdateQueueCount++] = obj;
            }
        }
    }

    sub_08030C00();

    for (queueIndex = 0; queueIndex < g_dwOamQueueCount; queueIndex++) {
        obj = g_apOamQueue[queueIndex];
        if (!(obj->dwFlags & ObjectFlagSkipSpriteFrameUpdate))
            UpdateObjectSpriteFrame(obj, mode);

        if (mode == 1) {
            oamResult = UpdateObjectOamCells(obj);
            if (obj->bDrawLayer != layer)
                while (layer < obj->bDrawLayer) {
                    sub_080317EC(layer);
                    layer++;
                }

            if (oamResult != 0) {
                anyOamWork = 1;
                if (oamResult == 2)
                    g_ObjectPoolState.apTileUpdateQueue[g_ObjectPoolState.bTileUpdateQueueCount++] = obj;
            }
        }
    }

    if (mode == 1) {
        if (g_ObjectPoolState.bExtraOamPassEnabled_candidate != 0) {
            for (queueIndex = 0; queueIndex < g_dwOamQueueCount; queueIndex++) {
                obj = g_apOamQueue[queueIndex];
                if (obj->dwFlags & ObjectFlagExtraOamPass) {
                    obj->bDrawFlags |= ObjectDrawFlagExtraOamPass;
                    UpdateObjectOamCells(obj);
                    obj->bDrawFlags &= ~ObjectDrawFlagExtraOamPass;
                }
            }
        }

        while (layer <= 3) {
            sub_080317EC(layer);
            layer++;
        }
    }

    if (mode == 1)
        sub_08030140();

    return anyOamWork;
}

#include "types.h"
#include "object.h"
#include "mem.h"
#include "vblank.h"

// Runs from vblank callbacks. Tile changes that TickObjectList queued take
// effect only on a vblank that swaps the OAM shadow buffers, so the buffer
// still on screen never points at tiles that were freed or reloaded.
void CommitQueuedObjectTileUpdates(void)
{
    s32 i;
    Object *obj;

    if (g_pVBlankState->wOamFrameReady == 1) {
        for (i = 0; i < g_ObjectPoolState.bTileUpdateQueueCount; i++) {
            obj = g_ObjectPoolState.apTileUpdateQueue[i];
            if (obj->dwFlags & ObjectFlagPendingDestroy) {
                ReleaseObjectOffscreenVramTiles(obj);
            } else if (obj->dwFlags & ObjectFlagAnimFrameLoaded) {
                obj->dwFlags &= ~ObjectFlagAnimFrameLoaded;
                obj->wOamTileIndex = obj->wVramTileAllocId;
            }
        }
        g_ObjectPoolState.bTileUpdateQueueCount = 0;
        ApplyDeferredObjTileFrees();
    }
}

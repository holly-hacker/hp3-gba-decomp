#include "types.h"
#include "actor.h"
#include "interrupts.h"
#include "vram.h"

// Runs from vblank callbacks. Tile changes that TickActorList queued take
// effect only on a vblank that swaps the OAM shadow buffers, so the buffer
// still on screen never points at tiles that were freed or reloaded.
void CommitQueuedActorTileUpdates(void)
{
    s32 i;
    Actor *actor;

    if (g_pVBlankState->wOamFrameReady == 1) {
        for (i = 0; i < g_ActorPoolState.bTileUpdateQueueCount; i++) {
            actor = g_ActorPoolState.apTileUpdateQueue[i];
            if (actor->dwFlags & ActorFlagPendingDestroy) {
                ReleaseActorOffscreenVramTiles(actor);
            } else if (actor->dwFlags & ActorFlagAnimFrameLoaded) {
                actor->dwFlags &= ~ActorFlagAnimFrameLoaded;
                actor->oam.tileNum = actor->wVramTileAllocId;
            }
        }
        g_ActorPoolState.bTileUpdateQueueCount = 0;
        ApplyDeferredObjTileFrees();
    }
}

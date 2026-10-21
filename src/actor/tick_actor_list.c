#include "types.h"
#include "modes.h"
#include "actor.h"
#include "main.h"

// Runs one update pass over an actor list. TickActor runs for every actor
// (from the tail when the mode flags allow the full pass), then the actors
// TickActor queued are drawn: the sprite-frame queue, then the depth-sorted OAM
// queue, flushing each draw layer's particles as the sort crosses its boundary.
// Returns 1 if any actor's OAM update reported work.
u32 TickActorList(ActiveActorListState *list, u8 mode)
{
    Actor *actor;
    Actor *next;
    u32 orbit;
    u32 posX;
    u32 posY;
    u32 oamResult;
    u32 queueIndex;
    u32 layer;
    u32 anyOamWork;
    void (*pfnCheckCollisions)(s32, Actor **) = CheckActorCollisionsIwram;
    void (*pfnSortActors)(Actor **, u32) = SortActorsByDepthIwram;

    anyOamWork = 0;
    g_bSpriteFrameQueueCount = 0;
    g_dwOamQueueCount = 0;
    g_ActorPoolState.bTileUpdateQueueCount = 0;
    g_dwCollisionQueueCount = 0;
    layer = 0;

    if ((g_dwGameModeFlags & (GameModeFlagUnk8 | GameModeFlagUnk40000)) == GameModeFlagUnk8) {
        actor = (Actor *)list->pHead;
        while (actor != NULL) {
            next = (Actor *)actor->node.pNext;
            TickActor(actor, mode);
            actor = next;
        }
    }
    else {
        actor = (Actor *)list->pUnk4;
        while (actor != NULL) {
            next = (Actor *)actor->node.pPrev;
            TickActor(actor, mode);
            actor = next;
        }

        if (!(g_dwGameModeFlags & GameModeFlagScreenTransition) && g_dwCollisionQueueCount != 0 &&
            list == &g_ActiveActorListState)
            pfnCheckCollisions(g_dwCollisionQueueCount, g_apCollisionQueue);

        for (actor = (Actor *)list->pHead; actor != NULL; actor = (Actor *)actor->node.pNext) {
            orbit = actor->orbitState.radii.dwOrbitRadii;
            if (actor->pOwnerActor != NULL)
                FollowOwnerActor(actor);

            posX = actor->posPrev.x;
            posY = actor->posPrev.y;
            actor->pos.x = posX;
            actor->pos.y = posY;
            if (orbit != 0)
                ApplyActorOrbitMotion(actor);
        }
    }

    if (mode == 1 && g_dwActorDepthSortEnabled != 0 && g_dwOamQueueCount > 1)
        pfnSortActors(g_apOamQueue, g_dwOamQueueCount);

    for (queueIndex = g_bSpriteFrameQueueCount; queueIndex != 0; queueIndex--) {
        actor = g_apSpriteFrameQueue[queueIndex - 1];
        if (!(actor->dwFlags & ActorFlagSkipSpriteFrameUpdate))
            UpdateActorSpriteFrame(actor, mode);

        if (mode == 1) {
            oamResult = UpdateActorOamCells(actor);
            if (oamResult != 0) {
                anyOamWork = 1;
                if (oamResult == 2)
                    g_ActorPoolState.apTileUpdateQueue[g_ActorPoolState.bTileUpdateQueueCount++] = actor;
            }
        }
    }

    BucketParticlesByPriority();

    for (queueIndex = 0; queueIndex < g_dwOamQueueCount; queueIndex++) {
        actor = g_apOamQueue[queueIndex];
        if (!(actor->dwFlags & ActorFlagSkipSpriteFrameUpdate))
            UpdateActorSpriteFrame(actor, mode);

        if (mode == 1) {
            oamResult = UpdateActorOamCells(actor);
            if (actor->oam.priority != layer)
                while (layer < actor->oam.priority) {
                    TickParticleLayer(layer);
                    layer++;
                }

            if (oamResult != 0) {
                anyOamWork = 1;
                if (oamResult == 2)
                    g_ActorPoolState.apTileUpdateQueue[g_ActorPoolState.bTileUpdateQueueCount++] = actor;
            }
        }
    }

    if (mode == 1) {
        if (g_ActorPoolState.bExtraOamPassEnabled_candidate != 0) {
            for (queueIndex = 0; queueIndex < g_dwOamQueueCount; queueIndex++) {
                actor = g_apOamQueue[queueIndex];
                if (actor->dwFlags & ActorFlagExtraOamPass) {
                    actor->bDrawFlags |= ActorDrawFlagExtraOamPass;
                    UpdateActorOamCells(actor);
                    actor->bDrawFlags &= ~ActorDrawFlagExtraOamPass;
                }
            }
        }

        while (layer <= 3) {
            TickParticleLayer(layer);
            layer++;
        }
    }

    if (mode == 1)
        CommitObjAffineMatrices();

    return anyOamWork;
}

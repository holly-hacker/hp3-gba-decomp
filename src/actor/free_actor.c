#include "types.h"
#include "actor.h"
#include "area.h"
#include "list.h"

// Releases actor back to the actor pool's free list; a no-op if it was
// already freed (wActorType == 0xFFFF is the freed sentinel).
void FreeActor(Actor *actor)
{
    u32 affineSlotState;

    if (actor->wActorType == 0xFFFF)
        return;

    if (actor->pfnDestructor)
        actor->pfnDestructor(actor);

    ReleaseActorPalette(actor);

    if (actor->dwFlags & ActorFlagRoomRecordBound)
        SetRoomActorPtr(0, actor->bRoomTileCol_candidate, actor->bRoomTileRow_candidate);

    actor->wActorType = 0xFFFF;

    affineSlotState = actor->oam.affineMode;
    if (affineSlotState == 1 || affineSlotState == 3)
        ReleaseActorAffineSlot(actor);

    if (g_dwActorListTicked_candidate == 1)
        ReleaseActorOffscreenVramTiles(actor);

    if (g_ActiveActorListState.pTail == (ListNode *)actor)
        g_ActiveActorListState.pTail = actor->node.pPrev;

    List_MoveToHead((ListNode **)&g_ActorPoolState.pFreeListHead, &g_ActiveActorListState.pHead, (ListNode *)actor);
}

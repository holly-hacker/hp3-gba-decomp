#include "actor.h"
#include "mem.h"
#include "list.h"

// Pops an actor off the free list and resets its default sentinel fields
// (no type, no room-tile binding, no VRAM tile allocation).
Actor *AllocDefaultActor(void)
{
    Actor *actor = (Actor *)AllocObjectFromFreeList(
        (ListNode **)&g_ActorPoolState.pFreeListHead,
        &g_ActiveActorListState.pHead, sizeof(Actor));

    if (g_ActiveActorListState.pUnk4 == NULL) {
        g_ActiveActorListState.pUnk4 = (ListNode *)actor;
    }
    actor->wFlags_0xAC |= 1;
    actor->wActorType = 0xFFFF;
    actor->wVramTileAllocId = 0xFFFF;
    actor->bRoomTileCol_candidate = 0xFF;
    actor->bRoomTileRow_candidate = 0xFF;
    return actor;
}

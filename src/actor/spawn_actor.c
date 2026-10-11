#include "types.h"
#include "actor.h"
#include "hw/mem.h"

// Same body as AllocDefaultActor, inlined here.
static inline Actor *AllocDefaultActorInline(void)
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

// Allocates an actor of the given type at pixel position (x, y) with the
// standard visible/animated flags. pPalette, when present, is passed to
// AttachActorPalette. Returns the new actor.
Actor *SpawnActor(u32 type, s32 x, s32 y, const ObjPalette *pPalette)
{
    Actor *actor = AllocDefaultActorInline();

    if (actor != NULL)
    {
        SnapActorPosition(actor, x << 16, y << 16);
        actor->wActorType = type;
        actor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic | ActorFlagHasAnimation
            | ActorFlagKeepPaletteSlot;
        actor->bDepthSortBias = 0x80;
        if (pPalette != NULL)
            AttachActorPalette(actor, pPalette);
    }
    return actor;
}

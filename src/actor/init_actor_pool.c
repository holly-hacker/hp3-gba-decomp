#include "arm_routines.h"
#include "mem.h"
#include "actor.h"
#include "list.h"
#include "hw/bios.h"

// Carves the actor free list out of g_ActorPoolState.pBuffer (0x69 actors,
// 0x128-byte stride) and relocates the per-frame sort/collision passes
// into IWRAM for speed.
void InitActorPool(void)
{
    ActorPoolAuxRecord **pAux;

    g_ActorPoolState.pBuffer = AllocZeroed(0x7968);

    pAux = &g_pActorPoolAuxBuffer;
    *pAux = AllocZeroed(0x104);
    g_ActorPoolState.pFreeListHead = BuildFreeList(g_ActorPoolState.pBuffer, 0x69, 0x128);

    bios_CPUSet(SortActorsByDepth, SortActorsByDepthIwram, 0x4000031);
    bios_CPUSet(CheckActorCollisions, CheckActorCollisionsIwram, 0x400007D);

    g_dwActorDepthSortEnabled = 1;
    g_dwUnk03001DC4 = 0;
}

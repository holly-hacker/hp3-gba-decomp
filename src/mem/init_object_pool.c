#include "mem.h"
#include "bios.h"

// Carves the object free list out of g_pObjectPoolBuffer (0x69 objects,
// 0x128-byte stride) and relocates the per-frame sort/collision passes
// into IWRAM for speed.
void InitObjectPool(void)
{
    void **pAux;

    g_pObjectPoolBuffer = AllocZeroed(0x7968);

    pAux = &g_pObjectPoolAuxBuffer;
    *pAux = AllocZeroed(0x104);
    sFreeObjectListHead = BuildFreeList(g_pObjectPoolBuffer, 0x69, 0x128);

    bios_CPUSet(SortObjectsByDepth_candidate, g_pSortObjectsIwram, 0x4000031);
    bios_CPUSet(CheckObjectCollisions_candidate, g_pCheckObjectCollisionsIwram, 0x400007D);

    g_dwObjectListActive_candidate = 1;
    g_dwUnk03001DC4 = 0;
}

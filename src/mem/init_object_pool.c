#include "mem.h"
#include "bios.h"

// Carves the object free list out of g_ObjectPoolState.pBuffer (0x69 objects,
// 0x128-byte stride) and relocates the per-frame sort/collision passes
// into IWRAM for speed.
void InitObjectPool(void)
{
    ObjectPoolAuxRecord **pAux;

    g_ObjectPoolState.pBuffer = AllocZeroed(0x7968);

    pAux = &g_pObjectPoolAuxBuffer;
    *pAux = AllocZeroed(0x104);
    g_ObjectPoolState.pFreeListHead = BuildFreeList(g_ObjectPoolState.pBuffer, 0x69, 0x128);

    bios_CPUSet(SortObjectsByDepth, g_pSortObjectsIwram, 0x4000031);
    bios_CPUSet(CheckObjectCollisions, g_pCheckObjectCollisionsIwram, 0x400007D);

    g_dwObjectListActive_candidate = 1;
    g_dwUnk03001DC4 = 0;
}

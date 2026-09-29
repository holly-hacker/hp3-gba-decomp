#include "hw/mem.h"
#include "overworld/room.h"
#include "hw/bios.h"

// Relocates FindFreeObjTileRun into IWRAM for speed, then resets the OBJ
// tile allocation bitmaps.
void InstallIwramFindFreeObjTileRun(void)
{
    bios_CPUSet(FindFreeObjTileRun, g_pFindFreeObjTileRunIwram, 0x4000027);
    InitObjTileAllocBitmaps(0);
}

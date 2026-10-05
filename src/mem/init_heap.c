#include "hw/mem.h"
#include "hw/io_regs.h"

// Registers pool 0 over EWRAM above the statically linked EWRAM section.
void InitHeap(void)
{
    InitMemoryPool(0, g_abEwramHeap, EWRAM_END);
}

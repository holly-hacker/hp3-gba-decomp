#include "hw/mem.h"

// Registers pool 0 over EWRAM above the statically linked EWRAM section.
void InitHeap(void)
{
    InitMemoryPool(0, (void *)0x02002800, (void *)0x02040000);
}

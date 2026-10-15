#include "mem.h"

// Returns 1; nothing calls it or stores its address.
u32 HeapStubReturnOne(void)
{
    return 1;
}

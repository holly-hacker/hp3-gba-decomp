#include "types.h"
#include "object.h"
#include "mem.h"

// Zeroes the object pool's shared VRAM tile records. Unused.
void ClearObjectPoolAuxBuffer(void)
{
    memset(g_pObjectPoolAuxBuffer, 0, sizeof(ObjectPoolAuxRecord) * 5);
}

// Sets the byte gating TickObjectList's extra OAM pass. Unused.
void SetExtraOamPassPriority(u8 priority)
{
    g_ObjectPoolState.bExtraOamPassEnabled_candidate = priority;
}

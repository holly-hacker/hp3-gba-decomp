#include "types.h"
#include "actor.h"
#include "hw/mem.h"

// Zeroes the actor pool's shared VRAM tile records. Unused.
void ClearActorPoolAuxBuffer(void)
{
    memset(g_pActorPoolAuxBuffer, 0, sizeof(ActorPoolAuxRecord) * 5);
}

// Sets the byte gating TickActorList's extra OAM pass. Unused.
void SetExtraOamPassPriority(u8 priority)
{
    g_ActorPoolState.bExtraOamPassEnabled_candidate = priority;
}

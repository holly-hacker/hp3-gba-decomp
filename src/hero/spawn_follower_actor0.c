#include "hero.h"

Actor *SpawnFollowerActor0(u32 characterId)
{
    g_pFollowerActor0 = SpawnPartyFollowerActor(characterId);
    g_pFollowerActor0->pfnTick = TickPartyFollowerActor;
    return g_pFollowerActor0;
}

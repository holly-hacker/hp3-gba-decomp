#include "hero.h"

Actor *SpawnFollowerActor1(u32 characterId)
{
    g_pFollowerActor1 = SpawnPartyFollowerActor(characterId);
    g_pFollowerActor1->pfnTick = TickPartySecondFollowerActor;
    return g_pFollowerActor1;
}

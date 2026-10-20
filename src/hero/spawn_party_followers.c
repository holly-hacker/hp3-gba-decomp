#include "hero.h"

// Respawns the followers whose characters are in the party.
void SpawnPartyFollowers(void)
{
    g_dwUnk030033A8 = 0;
    if (g_bPartyCharId1 != 0xFF)
        SpawnFollowerActor0(g_bPartyCharId1);
    if (g_bPartyCharId2 != 0xFF)
        SpawnFollowerActor1(g_bPartyCharId2);
}

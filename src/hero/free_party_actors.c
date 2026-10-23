#include "actor.h"
#include "dialog.h"
#include "hero.h"
#include "mem.h"

// Frees the party's actors and trail, keeping the followers' characters for
// SpawnPartyFollowers.
void FreePartyActors(void)
{
    if (g_pFollowerActor0 != NULL)
    {
        g_bPartyCharId1 = g_pFollowerActor0->wSubtype;
        FreeActor(g_pFollowerActor0);
        g_pFollowerActor0 = NULL;
    }
    if (g_pFollowerActor1 != NULL)
    {
        g_bPartyCharId2 = g_pFollowerActor1->wSubtype;
        FreeActor(g_pFollowerActor1);
        g_pFollowerActor1 = NULL;
    }
    FreeActor(g_pPlayerActor);
    g_pPlayerActor = NULL;
    FreeBlock(g_pPartyTrail);
    FreeFieldHudActors();
}

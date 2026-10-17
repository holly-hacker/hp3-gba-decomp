#include "types.h"
#include "overworld/overworld.h"
#include "hero.h"

void ResetPartyState(void)
{
    g_pFieldSpellNameActor = NULL;
    g_pMapNameTextActor = NULL;
    g_dwUnk030033A8 = 0;
    g_pFieldSpellPortraitActor = NULL;
    g_pMapNamePopupActor = NULL;
    g_bPartyCharId0 = 5;
    g_bPartyCharId1 = 0xFF;
    g_bPartyCharId2 = 0xFF;
    g_pFollowerActor0 = NULL;
    g_pFollowerActor1 = NULL;
    g_bSelectedFieldSpell = 0;
}

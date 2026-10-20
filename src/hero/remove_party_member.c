#include "types.h"
#include "hero.h"
#include "overworld/room_script.h"
#include "overworld/overworld.h"

// Removing the leader moves each follower's character up one place, so the last actor
// is the one destroyed.
void RemovePartyMember(u8 characterId)
{
    if (g_pFollowerActor1 != NULL)
    {
        if (g_pFollowerActor1->wCharacterId_candidate == characterId)
        {
            DestroyPartyMemberActor(g_pFollowerActor1);
            g_pFollowerActor1 = NULL;
            g_bPartyCharId2 = 0xFF;
            return;
        }
    }
    else if (g_pFollowerActor0->wCharacterId_candidate == characterId)
    {
        DestroyPartyMemberActor(g_pFollowerActor0);
        g_pFollowerActor0 = NULL;
        g_bPartyCharId1 = 0xFF;
        return;
    }

    if (g_pPlayerActor->wCharacterId_candidate == characterId)
    {
        if (g_pFollowerActor1 == NULL)
        {
            SwapPartyMemberCharacters(g_pPlayerActor, g_pFollowerActor0);
            DestroyPartyMemberActor(g_pFollowerActor0);
            g_pFollowerActor0 = NULL;
            g_bPartyCharId1 = 0xFF;
        }
        else
        {
            SwapPartyMemberCharacters(g_pPlayerActor, g_pFollowerActor0);
            SwapPartyMemberCharacters(g_pFollowerActor0, g_pFollowerActor1);
            DestroyPartyMemberActor(g_pFollowerActor1);
            g_pFollowerActor1 = NULL;
            g_bPartyCharId2 = 0xFF;
        }
        g_bSelectedFieldSpell = GetPartyMasterStatsSlot_candidate(g_bPartyCharId0) * 3;
        RefreshFieldSpellHud(g_pFieldSpellIconActor);
    }
    else
    {
        SwapPartyMemberCharacters(g_pFollowerActor0, g_pFollowerActor1);
        DestroyPartyMemberActor(g_pFollowerActor1);
        g_pFollowerActor1 = NULL;
        g_bPartyCharId2 = 0xFF;
    }
}

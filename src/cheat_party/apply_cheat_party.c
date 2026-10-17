#include "types.h"
#include "cheat_party.h"
#include "overworld/overworld.h"
#include "hero.h"

// An empty slot (0) clears the party id to 0xFF and drops the follower actor.
void ApplyCheatParty(void)
{
    g_bPartyCharId0 = (s32)g_CheatPartyState.adwCharacter[0] > 0 ? g_CheatPartyState.adwCharacter[0] - 1 : 0xFF;
    if (g_bPartyCharId0 == 0xFF)
        g_pPlayerActor = NULL;

    g_bPartyCharId1 = (s32)g_CheatPartyState.adwCharacter[1] > 0 ? g_CheatPartyState.adwCharacter[1] - 1 : 0xFF;
    if (g_bPartyCharId1 == 0xFF)
        g_pFollowerActor0 = NULL;

    g_bPartyCharId2 = (s32)g_CheatPartyState.adwCharacter[2] > 0 ? g_CheatPartyState.adwCharacter[2] - 1 : 0xFF;
    if (g_bPartyCharId2 == 0xFF)
        g_pFollowerActor1 = NULL;
}

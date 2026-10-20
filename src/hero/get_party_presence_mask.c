#include "hero.h"

// The ItemCharacterMask bits of the party's characters.
u32 GetPartyPresenceMask(void)
{
    u32 mask;

    mask = GetCharPresenceBit(g_bPartyCharId0);
    mask |= GetCharPresenceBit(g_bPartyCharId1);
    mask |= GetCharPresenceBit(g_bPartyCharId2);
    return mask;
}

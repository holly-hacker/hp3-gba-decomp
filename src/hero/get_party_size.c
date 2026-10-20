#include "hero.h"

// Party members that fight; Buckbeak (character 8) does not count.
u32 GetPartySize(void)
{
    if (g_bPartyCharId1 == 0xFF || g_bPartyCharId1 == 8)
        return 1;
    if (g_bPartyCharId2 == 0xFF || g_bPartyCharId2 == 8)
        return 2;
    return 3;
}

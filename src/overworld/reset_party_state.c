#include "types.h"
#include "overworld/overworld.h"

void ResetPartyState(void)
{
    g_pFieldSpellNameObject = NULL;
    g_pMapNameTextObject = NULL;
    g_dwUnk030033A8 = 0;
    g_pFieldSpellPortraitObject = NULL;
    g_pMapNamePopupObject = NULL;
    g_bPartyCharId0 = 5;
    g_bPartyCharId1 = 0xFF;
    g_bPartyCharId2 = 0xFF;
    g_pFollowerObject0 = NULL;
    g_pFollowerObject1 = NULL;
    g_bSelectedFieldSpell = 0;
}

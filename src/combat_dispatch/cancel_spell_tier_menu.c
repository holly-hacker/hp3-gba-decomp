#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"

void CancelSpellTierMenu(u32 fighterType, BattleFighter *pFighter)
{
    ShowSpellChoiceMenu(g_pFightState->bMenuFighterIndex, g_pFightState->bSpellMenuCursor);
}

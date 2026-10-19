#include "types.h"
#include "combat_fighter.h"
#include "items.h"
#include "combat.h"

// The level's agility less the agility of each equipped item. No callers.
s32 ComputeEquippedAgility(u32 character)
{
    const CharacterLevelEntry *table;
    u32 item;
    s32 agility;
    s32 slot;

    item = 0;
    switch (character)
    {
    case Harry:
    default:
        table = g_pHarryLevelTable;
        break;
    case Hermione:
        table = g_pHermioneLevelTable;
        break;
    case Ron:
        table = g_pRonLevelTable;
        break;
    }

    agility = table[g_aPartyMasterStats[character].stats.bLevel].bAgility;
    for (slot = 0; slot < EQUIP_SLOT_COUNT; slot++)
    {
        // BUG: item is never read from the slot, so every term is item 0's agility.
        if (item != 0xFF)
            agility -= GetItemAgility(item);
    }

    return agility;
}

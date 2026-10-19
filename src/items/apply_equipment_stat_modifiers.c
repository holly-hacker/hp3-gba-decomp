#include "types.h"
#include "combat_fighter.h"
#include "items.h"
#include "combat.h"

// Recomputes each party member's base stats from their level, then lowers
// Def/M.Def percentages (lower is better) and Agi by each equipped item.
void ApplyEquipmentStatModifiers(void)
{
    s32 character;
    s32 slot;

    for (character = 0; character < 3; character++)
    {
        RecomputeBaseStatsFromLevel(character);

        for (slot = 0; slot < EQUIP_SLOT_COUNT; slot++)
        {
            u32 item = g_ItemInventory.aabEquipped[character][slot];

            if (item != 0xFF)
            {
                s32 agility;

                if (g_aPartyMasterStats[character].bDefenseFactorPercent >= g_pItemTable[item].stats.equipment.nDefenseX2 / 2)
                    g_aPartyMasterStats[character].bDefenseFactorPercent -= g_pItemTable[item].stats.equipment.nDefenseX2 / 2;
                else
                    g_aPartyMasterStats[character].bDefenseFactorPercent = 0;

                if (g_aPartyMasterStats[character].bMagicDefensePercent >= g_pItemTable[item].nMagicDefense)
                    g_aPartyMasterStats[character].bMagicDefensePercent -= g_pItemTable[item].nMagicDefense;
                else
                    g_aPartyMasterStats[character].bMagicDefensePercent = 0;

                agility = g_aPartyMasterStats[character].bAgility;
                agility -= g_pItemTable[item].stats.equipment.nAgility;
                if (agility < 0)
                    agility = 0;
                if (agility > 255)
                    agility = 255;
                g_aPartyMasterStats[character].bAgility = agility;
            }
        }
    }
}

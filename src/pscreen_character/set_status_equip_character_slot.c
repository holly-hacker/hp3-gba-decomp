#include "pscreen_character.h"

void SetStatusEquipCharacterSlot(u32 slot)
{
    if (g_bStatusEquipCharacterSlot != slot)
    {
        DrawStatusEquipCharacterStats(g_bStatusEquipCharacterSlot, 1);
        g_bStatusEquipCharacterSlot = slot;
        DrawStatusEquipCharacterStats(g_bStatusEquipCharacterSlot, 6);
    }
}

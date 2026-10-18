#include "pscreen_character.h"
#include "hero.h"

u8 StatusEquipSlotToColumn(u8 slot)
{
    u8 column = 0;

    switch (GetPartySize())
    {
    case 1:
        column = 1;
        break;

    case 2:
        if (g_StatusEquipCharacterSelect.adwSlotPresent[0] && g_StatusEquipCharacterSelect.adwSlotPresent[1])
        {
            if (slot == 1)
                column = 2;
        }
        else if (g_StatusEquipCharacterSelect.adwSlotPresent[1] && g_StatusEquipCharacterSelect.adwSlotPresent[2])
        {
            if (slot == 1)
                column = 0;
            else
                column = 2;
        }
        else if (g_StatusEquipCharacterSelect.adwSlotPresent[0] && g_StatusEquipCharacterSelect.adwSlotPresent[2])
        {
            column = slot;
        }
        break;

    case 3:
        column = slot;
        break;
    }

    return column;
}

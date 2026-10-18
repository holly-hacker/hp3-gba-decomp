#include "sound.h"
#include "pscreen_character.h"
#include "pscreen_equip.h"
#include "items.h"
#include "items_list.h"
#include "constants/items.h"

u32 EquipStatusEquipItemSelection(void)
{
    if (g_StatusEquipItemSelect.dwHasItems != 0)
    {
        if (GetItemListSelection() != ITEM_REMOVE)
        {
            PlaySoundById(0x1B);
            return EquipItemInSlot(g_dwStatusEquipCharacter, GetItemListSelection());
        }
        else
        {
            PlaySoundById(0x1B);
            return UnequipItemFromSlot(g_dwStatusEquipCharacter, g_dwStatusEquipSlotType);
        }
    }

    return 0;
}

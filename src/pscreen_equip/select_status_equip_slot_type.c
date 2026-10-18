#include "sound.h"
#include "pscreen_equip.h"

void SelectStatusEquipSlotType(u32 slotType)
{
    PlaySoundById(1);
    g_dwStatusEquipSlotType = slotType;
}

#include "types.h"
#include "actor.h"
#include "pscreen_status_equip.h"

void FreeStatusEquipSlotActors(void)
{
    s32 i;

    for (i = 0; i < 6; i++)
    {
        FreeActor(g_StatusEquipSlotSelect.apSlotFrames[i]);
        if (g_StatusEquipSlotSelect.apSlotItems[i] != NULL)
            FreeActor(g_StatusEquipSlotSelect.apSlotItems[i]);
    }
}

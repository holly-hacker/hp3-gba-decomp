#include "actor.h"
#include "pscreen_status_equip.h"

// Glides the cursor to the selected slot.
void TickStatusEquipSlotCursor(Actor *pCursor)
{
    SetActorMoveTargetWithDuration(pCursor, g_aStatusEquipSlots[g_bStatusEquipSlot].nX,
                                   g_aStatusEquipSlots[g_bStatusEquipSlot].nY, 2);
}

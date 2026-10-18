#include "actor.h"
#include "pscreen_status_equip.h"

void UpdateStatusEquipSlotCursorAnim(void)
{
    if (IsStatusEquipSlotSelectable())
        SetActorAnimData(g_StatusEquipSlotSelect.pCursor, &g_StatusEquipSlotCursorAsset,
                         g_abStatusEquipSlotCursorPulseAnim, 0);
    else
        SetActorAnimData(g_StatusEquipSlotSelect.pCursor, &g_StatusEquipSlotCursorAsset,
                         g_abStatusEquipSlotCursorDimAnim, 0);
}

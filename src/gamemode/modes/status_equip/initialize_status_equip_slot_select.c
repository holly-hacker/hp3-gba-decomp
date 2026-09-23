#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "object.h"
#include "status_equip.h"

void InitializeStatusEquipSlotSelect(void)
{
    sub_0803094C(14);
    sub_0803094C(15);
    g_GameModeStackContext.dwModeSubState = 0x10;
    g_StatusEquipSlotSelect.pCharacter = sub_0803A030(g_dwStatusEquipCharacter);
    DrawStatusEquipStatsPanel();
    g_GameModeStackContext.dwModeState = 1;

    g_StatusEquipSlotSelect.pCursor = SpawnObject(10, g_aStatusEquipSlots[g_bStatusEquipSlot].nX + 20,
                                                  g_aStatusEquipSlots[g_bStatusEquipSlot].nY,
                                                  g_StatusEquipSlotCursorSpawnData);
    g_StatusEquipSlotSelect.pCursor->pfnTick = TickStatusEquipSlotCursor;
    sub_0803A630();
}

#include "types.h"
#include "graphics/display.h"
#include "modes.h"
#include "actor.h"
#include "pscreen_status_equip.h"
#include "gen/graphics/overworld.h"
#include "pscreen_character.h"

void InitializeStatusEquipSlotSelect(void)
{
    ReserveObjPaletteSlot(14);
    ReserveObjPaletteSlot(15);
    g_GameModeStackContext.dwModeSubState = 0x10;
    g_StatusEquipSlotSelect.pCharacter = sub_0803A030(g_dwStatusEquipCharacter);
    DrawStatusEquipStatsPanel();
    g_GameModeStackContext.dwModeState = 1;

    g_StatusEquipSlotSelect.pCursor = SpawnActor(10, g_aStatusEquipSlots[g_bStatusEquipSlot].nX + 20,
                                                  g_aStatusEquipSlots[g_bStatusEquipSlot].nY,
                                                  (const ObjPalette *)gStatusEquipSlotCursorPalette);
    g_StatusEquipSlotSelect.pCursor->pfnTick = TickStatusEquipSlotCursor;
    sub_0803A630();
}

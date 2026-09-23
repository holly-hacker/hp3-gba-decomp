#include "types.h"
#include "display.h"
#include "in_game_menu.h"
#include "main_menu.h"
#include "object.h"
#include "status_equip.h"

void InitializeStatusEquipCharacterSelectLastCursor(void)
{
    sub_080320A4();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();

    g_bStatusEquipCharacterSlot = StatusEquipCharacterToSlot(g_dwStatusEquipCharacter);
    SetObjectPosition(g_pMenuCursorObject, g_bStatusEquipCharacterSlot * 72 + 24, 68);
}

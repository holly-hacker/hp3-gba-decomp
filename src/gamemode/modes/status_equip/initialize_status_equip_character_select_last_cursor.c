#include "types.h"
#include "graphics/display.h"
#include "menu/in_game_menu.h"
#include "menu/main_menu.h"
#include "graphics/object.h"
#include "menu/status_equip.h"

void InitializeStatusEquipCharacterSelectLastCursor(void)
{
    StartMenuFadeIn();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();

    g_bStatusEquipCharacterSlot = StatusEquipCharacterToSlot(g_dwStatusEquipCharacter);
    SetObjectPosition(g_pMenuCursorObject, g_bStatusEquipCharacterSlot * 72 + 24, 68);
}

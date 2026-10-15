#include "types.h"
#include "game/game_modes.h"
#include "menu/items_menu.h"
#include "menu/status_equip.h"
#include "inventory.h"

void InitializeItemUseScreen(void)
{
    sub_08039A20(UseRestorePotion(g_dwStatusEquipCharacter, g_dwItemUseItem, g_dwItemUseQuantity));
    g_GameModeStackContext.dwModeSubState = 0x10;
    g_GameModeStackContext.dwModeState = 1;
}

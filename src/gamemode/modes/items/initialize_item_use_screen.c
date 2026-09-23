#include "types.h"
#include "game_modes.h"
#include "items_menu.h"
#include "status_equip.h"

void InitializeItemUseScreen(void)
{
    sub_08039A20(sub_080269E0(g_dwStatusEquipCharacter, g_dwItemUseItem, g_dwItemUseQuantity));
    g_GameModeStackContext.dwModeSubState = 0x10;
    g_GameModeStackContext.dwModeState = 1;
}

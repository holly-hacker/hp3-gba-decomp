#include "types.h"
#include "display.h"
#include "in_game_menu.h"
#include "status_equip.h"

void InitializeStatusEquipCharacterSelect(void)
{
    sub_080320A4();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();
}

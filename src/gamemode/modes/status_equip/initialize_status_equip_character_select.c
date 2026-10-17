#include "types.h"
#include "graphics/display.h"
#include "pause_menu.h"
#include "menu/status_equip.h"

void InitializeStatusEquipCharacterSelect(void)
{
    StartMenuFadeIn();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();
}

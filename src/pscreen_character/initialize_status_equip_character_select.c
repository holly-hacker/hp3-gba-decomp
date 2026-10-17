#include "types.h"
#include "pause_menu.h"
#include "pscreen_character.h"
#include "screen_transitions.h"

void InitializeStatusEquipCharacterSelect(void)
{
    StartMenuFadeIn();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();
}

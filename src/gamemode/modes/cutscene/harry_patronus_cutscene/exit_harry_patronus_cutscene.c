#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"

void ExitHarryPatronusCutscene(void)
{
    sub_08026254();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetFadeToWhite(0x3F, 0);
}

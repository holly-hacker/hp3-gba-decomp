#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "interrupts.h"

void ExitHarryPatronusCutscene(void)
{
    RestoreDefaultVBlankCallback();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetFadeToWhite(0x3F, 0);
}

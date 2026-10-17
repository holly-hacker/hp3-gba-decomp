#include "types.h"
#include "battle/battle.h"
#include "interrupts.h"
#include "patronus_cutscene.h"
#include "screen_transitions.h"

void ExitHarryPatronusCutscene(void)
{
    RestoreDefaultVBlankCallback();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetFadeToWhite(0x3F, 0);
}

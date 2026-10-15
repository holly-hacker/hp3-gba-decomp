#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "interrupts.h"
#include "mem.h"
#include "actor.h"

void ExitHippogriffFliesIntoAirCutscene(void)
{
    RestoreDefaultVBlankCallback();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}

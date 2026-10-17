#include "types.h"
#include "ending_cutscene.h"
#include "battle/battle.h"
#include "interrupts.h"
#include "mem.h"
#include "actor.h"
#include "screen_transitions.h"

void ExitHippogriffFliesIntoAirCutscene(void)
{
    RestoreDefaultVBlankCallback();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}

#include "types.h"
#include "mem.h"
#include "actor.h"
#include "screen_transitions.h"

void ExitCheatWizardCards(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}

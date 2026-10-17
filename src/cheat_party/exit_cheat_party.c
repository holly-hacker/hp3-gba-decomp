#include "types.h"
#include "cheat_party.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"
#include "screen_transitions.h"

void ExitCheatParty(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ApplyCheatParty();
    FreeAllActors(&g_ActiveActorListState.pHead);
}

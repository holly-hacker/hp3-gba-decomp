#include "types.h"
#include "cheat_party.h"
#include "graphics/display.h"
#include "hw/mem.h"

void ExitCheatParty(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ApplyCheatParty();
    FreeAllActors(&g_ActiveActorListState.pHead);
}

#include "types.h"
#include "cheat_party.h"
#include "graphics/display.h"
#include "hw/mem.h"

void ExitCheatParty(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0800B40C();
    FreeAllActors(&g_ActiveActorListState.pHead);
}

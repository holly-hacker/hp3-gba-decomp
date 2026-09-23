#include "types.h"
#include "battle.h"
#include "display.h"
#include "mem.h"

void ExitHippogriffFliesIntoAirCutscene(void)
{
    sub_08026254();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_080015D4(&g_ActiveObjectListState.pHead);
}

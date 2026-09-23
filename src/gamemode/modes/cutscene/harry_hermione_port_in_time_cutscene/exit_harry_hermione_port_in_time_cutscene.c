#include "types.h"
#include "display.h"
#include "harry_hermione_port_in_time_cutscene.h"
#include "mem.h"
#include "overworld.h"

void ExitHarryHermionePortInTimeCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_080015D4(&g_ActiveObjectListState.pHead);
    sub_0802DDAC();
    sub_0803EA3C();
}

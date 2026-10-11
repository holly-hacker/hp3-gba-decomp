#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "hw/mem.h"

void ExitHippogriffFliesIntoAirCutscene(void)
{
    sub_08026254();
    PlayScreenTransitionOutByIndex(0x3F, 2);
    FreeAllActors(&g_ActiveActorListState.pHead);
}

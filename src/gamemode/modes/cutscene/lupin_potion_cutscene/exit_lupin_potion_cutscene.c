#include "types.h"
#include "battle.h"
#include "display.h"
#include "mem.h"
#include "room.h"

void ExitLupinPotionCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    StopScanlineEffects();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_08030960(0);
    sub_08030960(1);
    sub_08030960(2);
}

#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "actor.h"
#include "overworld/room.h"

void ExitLupinPotionCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    StopScanlineEffects();
    FreeAllActors(&g_ActiveActorListState.pHead);
    UnreserveObjPaletteSlot(0);
    UnreserveObjPaletteSlot(1);
    UnreserveObjPaletteSlot(2);
}

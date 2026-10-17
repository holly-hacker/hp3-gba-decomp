#include "types.h"
#include "lupin_potion_cutscene.h"
#include "battle/battle.h"
#include "mem.h"
#include "actor.h"
#include "overworld/room.h"
#include "screen_transitions.h"
#include "video.h"

void ExitLupinPotionCutscene(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    StopScanlineEffects();
    FreeAllActors(&g_ActiveActorListState.pHead);
    UnreserveObjPaletteSlot(0);
    UnreserveObjPaletteSlot(1);
    UnreserveObjPaletteSlot(2);
}

#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"
#include "overworld/room.h"
#include "default_menu.h"
#include "minigame_menu.h"
#include "screen_transitions.h"

void ExitMinigameMenu(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticles();
    ClearScanlineEffects();
}

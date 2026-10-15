#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "actor.h"
#include "overworld/room.h"

void ExitWizardCrackerPopItDifficultySelect(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
    ResetBgLayers();
    FreeAllParticles();
    StopScanlineEffects();
}

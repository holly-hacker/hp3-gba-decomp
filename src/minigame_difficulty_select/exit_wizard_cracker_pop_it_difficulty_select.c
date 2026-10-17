#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"
#include "overworld/room.h"
#include "default_menu.h"
#include "minigame_difficulty_select.h"
#include "screen_transitions.h"

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

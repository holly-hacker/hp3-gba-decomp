#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "overworld/room.h"

void ExitWizardCrackerPopItDifficultySelect(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ExitMenuScreen();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_08007A90();
    FreeAllParticles();
    StopScanlineEffects();
}

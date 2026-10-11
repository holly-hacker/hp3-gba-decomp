#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "minigame/divination_tea.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

void ExitDivinationTeaMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);

    if (g_DivinationTea.pCursorActor != NULL)
    {
        ReleaseMenuCursor(g_DivinationTea.pCursorActor);
        g_DivinationTea.pCursorActor = NULL;
        FreeAllParticleEmitters();
        FreeAllParticles();
    }

    ResetPaletteAnimations();
    FreeAllActors(&g_ActiveActorListState.pHead);
    sub_0800A914();
}

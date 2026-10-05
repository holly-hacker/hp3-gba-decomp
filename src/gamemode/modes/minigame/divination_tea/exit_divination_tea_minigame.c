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

    if (g_DivinationTea.pCursorObject != NULL)
    {
        sub_0801DC6C(g_DivinationTea.pCursorObject);
        g_DivinationTea.pCursorObject = NULL;
        FreeAllParticleEmitters();
        FreeAllParticles();
    }

    ResetPaletteAnimations();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0800A914();
}

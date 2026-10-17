#include "types.h"
#include "battle/battle.h"
#include "char_block.h"
#include "color.h"
#include "graphics/display.h"
#include "tea_leaves_minigame.h"
#include "menu/main_menu.h"
#include "mem.h"
#include "actor.h"
#include "cursor.h"
#include "screen_transitions.h"

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
    FreeBgTileAnimations();
}

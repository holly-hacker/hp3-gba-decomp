#include "types.h"
#include "color.h"
#include "graphics/display.h"
#include "particles.h"
#include "mem.h"
#include "actor.h"
#include "menu/main_menu.h"
#include "landmarks.h"
#include "cursor.h"

void ExitUnusedHogwartsMapScreen(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ReleaseMenuCursor(g_pUnusedHogwartsMapCursor);
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}

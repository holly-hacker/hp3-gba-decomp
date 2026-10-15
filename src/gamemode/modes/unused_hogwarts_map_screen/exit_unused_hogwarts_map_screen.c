#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "graphics/palette.h"
#include "hw/mem.h"
#include "actor.h"
#include "menu/main_menu.h"
#include "menu/unused_hogwarts_map_screen.h"
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

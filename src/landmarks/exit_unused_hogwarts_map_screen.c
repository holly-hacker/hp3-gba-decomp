#include "color.h"
#include "particles.h"
#include "actor.h"
#include "landmarks.h"
#include "cursor.h"
#include "screen_transitions.h"

void ExitUnusedHogwartsMapScreen(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ReleaseMenuCursor(g_pUnusedHogwartsMapCursor);
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}

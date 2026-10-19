#include "color.h"
#include "modes.h"
#include "actor.h"
#include "gamecube.h"
#include "pscreen_gamecube.h"
#include "cursor.h"
#include "default_menu.h"
#include "screen_transitions.h"

void ExitGameCubeLink(void)
{
    TeardownJoybusHardware();

    if (GetPendingGameMode() == OwlCareMinigame)
        PlayScreenTransitionOutByIndex(0x3F, 2);

    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}

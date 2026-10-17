#include "types.h"
#include "battle/battle.h"
#include "color.h"
#include "graphics/display.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "gamecube.h"
#include "menu/gamecube_link.h"
#include "cursor.h"
#include "default_menu.h"

void ExitGameCubeLink(void)
{
    TeardownJoybusHardware();

    if (GetPendingGameMode_candidate() == OwlCareMinigame)
        PlayScreenTransitionOutByIndex(0x3F, 2);

    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}

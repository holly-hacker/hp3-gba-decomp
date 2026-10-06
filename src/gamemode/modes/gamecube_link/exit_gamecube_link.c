#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_modes.h"
#include "hw/mem.h"
#include "menu/gamecube_link.h"
#include "menu/main_menu.h"

void ExitGameCubeLink(void)
{
    TeardownJoybusHardware();

    if (GetPendingGameMode_candidate() == OwlCareMinigame)
        PlayScreenTransitionOutByIndex(0x3F, 2);

    ReleaseMenuCursor(g_pMenuCursorObject);
    g_pMenuCursorObject = NULL;
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}

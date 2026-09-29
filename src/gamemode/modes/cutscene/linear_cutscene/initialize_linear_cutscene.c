#include "types.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "cutscene/linear_cutscene.h"
#include "menu/main_menu.h"

void InitializeLinearCutscene(void)
{
    u32 cutsceneIndex;

    cutsceneIndex = g_GameModeStackContext.dwCurrentGameMode - Credits;
    g_dwLinearCutsceneIndex = cutsceneIndex;
    g_pLinearCutsceneObject = sub_0801D940(0);
    sub_0801D77C(cutsceneIndex);
    PlayScreenTransitionInByIndex(0x3F, 2);
}

#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "hw/mem.h"
#include "graphics/object.h"
#include "graphics/palette.h"

void ExitMainMenuScreen(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ReleaseMenuCursor(g_MainMenuState.pCursorObject);
    FreeAllParticleEmitters();
    FreeAllParticles();
    sub_08030960(0);
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_08007A90();
    ResetPaletteAnimations();
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
}

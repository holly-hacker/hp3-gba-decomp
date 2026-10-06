#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "game/game_modes.h"
#include "menu/gamecube_link.h"
#include "menu/in_game_menu.h"
#include "menu/main_menu.h"
#include "battle/battle.h"

void InitializeGameCubeLink(void)
{
    ClearResourceCacheSlots();

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
    {
        g_GameModeStackContext.dwModeState = 0;
        StartMenuFadeIn();
        BuildListMenu(&g_GameCubeLinkMenuDefinition);
        SpawnGameCubeLinkIconObjects();
    }
    else
    {
        g_GameModeStackContext.dwModeState = 1;
        BeginPauseMenuScreen(0);
        BuildListMenu(&g_GameCubeLinkMenuDefinition);
        SpawnGameCubeLinkIconObjects();
        PlayScreenTransitionInByIndex(0x3F, 2);
    }

    StartMainMenuPaletteEffect_candidate();
    ShowGameCubeLinkMessage(0x652);  // "Press the B Button to cancel."
    InitJoybusSession(DispatchGameCubeLinkCommand, 0x43, 0x83);
    g_GameCubeLinkScreenState.wResultTextId = 0xACF;
    g_GameCubeLinkScreenState.wStatusTextId = 0xACF;

    if (g_pMenuCursorObject != NULL)
    {
        ReleaseMenuCursor(g_pMenuCursorObject);
        FreeAllParticleEmitters();
        FreeAllParticles();
    }
}

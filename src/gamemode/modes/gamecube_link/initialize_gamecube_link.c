#include "types.h"
#include "graphics/display.h"
#include "particles.h"
#include "modes.h"
#include "gamecube.h"
#include "menu/gamecube_link.h"
#include "pause_menu.h"
#include "title.h"
#include "battle/battle.h"
#include "cursor.h"
#include "default_menu.h"

void InitializeGameCubeLink(void)
{
    ClearObjPaletteSlots();

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
    {
        g_GameModeStackContext.dwModeState = 0;
        StartMenuFadeIn();
        BuildListMenu(&g_GameCubeLinkMenuDefinition);
        SpawnGameCubeLinkIconActors();
    }
    else
    {
        g_GameModeStackContext.dwModeState = 1;
        BeginPauseMenuScreen(0);
        BuildListMenu(&g_GameCubeLinkMenuDefinition);
        SpawnGameCubeLinkIconActors();
        PlayScreenTransitionInByIndex(0x3F, 2);
    }

    StartMainMenuPaletteEffect();
    ShowGameCubeLinkMessage(0x652);  // "Press the B Button to cancel."
    InitJoybusSession(DispatchGameCubeLinkCommand, 0x43, 0x83);
    g_JoybusLinkState.wResultTextId = 0xACF;  // no text, so the first result is always drawn
    g_JoybusLinkState.wStatusTextId = 0xACF;  // no text

    if (g_pMenuCursorActor != NULL)
    {
        ReleaseMenuCursor(g_pMenuCursorActor);
        FreeAllParticleEmitters();
        FreeAllParticles();
    }
}

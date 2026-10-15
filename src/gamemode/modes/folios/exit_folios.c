#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_modes.h"
#include "mem.h"
#include "actor.h"
#include "menu/folios.h"
#include "menu/main_menu.h"
#include "cursor.h"

void ExitFolios(void)
{
    g_bFoliosMenuCursor = g_GameModeStackContext.dwModeScratchB;
    ClearBgTilemap(2);
    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllActors(&g_ActiveActorListState.pHead);
    FreeAllParticleEmitters();
    FreeAllParticles();
    ResetPaletteAnimations();
}

#include "types.h"
#include "background.h"
#include "battle/battle.h"
#include "color.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "pscreen_folio.h"
#include "cursor.h"
#include "default_menu.h"

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

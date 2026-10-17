#include "background.h"
#include "color.h"
#include "modes.h"
#include "title.h"
#include "actor.h"
#include "cursor.h"
#include "screen_transitions.h"

void ExitMainMenuScreen(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    ReleaseMenuCursor(g_MainMenuState.pCursorActor);
    FreeAllParticleEmitters();
    FreeAllParticles();
    UnreserveObjPaletteSlot(0);
    FreeAllActors(&g_ActiveActorListState.pHead);
    ResetBgLayers();
    ResetPaletteAnimations();
    g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
}

#include "modes.h"
#include "actor.h"
#include "pscreen_trade.h"
#include "cursor.h"
#include "default_menu.h"
#include "serial.h"

void ExitCardTrade(void)
{
    ClearMenuScreenOverlay();
    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllParticleEmitters();
    FreeAllParticles();
    FreeAllActors(&g_ActiveActorListState.pHead);

    if (GetPendingGameMode_candidate() == Connectivity)
        CloseSerialSession();
}

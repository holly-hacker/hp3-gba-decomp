#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "mem.h"
#include "actor.h"
#include "menu/card_trade.h"
#include "cursor.h"
#include "default_menu.h"

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

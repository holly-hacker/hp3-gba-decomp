#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "hw/mem.h"
#include "menu/card_trade.h"
#include "menu/main_menu.h"
#include "cursor.h"

void ExitCardTrade(void)
{
    ClearMenuTextLayer_candidate();
    ReleaseMenuCursor(g_pMenuCursorActor);
    g_pMenuCursorActor = NULL;
    FreeAllParticleEmitters();
    FreeAllParticles();
    FreeAllActors(&g_ActiveActorListState.pHead);

    if (GetPendingGameMode_candidate() == Connectivity)
        CloseSerialSession();
}

#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "hw/mem.h"
#include "menu/card_trade.h"
#include "menu/main_menu.h"

void ExitCardTrade(void)
{
    ClearMenuTextLayer_candidate();
    ReleaseMenuCursor(g_pMenuCursorObject);
    g_pMenuCursorObject = NULL;
    FreeAllParticleEmitters();
    FreeAllParticles();
    FreeAllObjects(&g_ActiveObjectListState.pHead);

    if (GetPendingGameMode_candidate() == Connectivity)
        CloseLinkSession();
}

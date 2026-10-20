#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"

void CancelFaintedAllyMenu(u32 fighterType, BattleFighter *pFighter)
{
    StopTargetFlash();
    OpenBattleTopMenu(g_pFightState->bMenuFighterIndex, 1);
}

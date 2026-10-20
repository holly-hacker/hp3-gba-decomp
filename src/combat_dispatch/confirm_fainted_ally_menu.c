#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "sound.h"

void ConfirmFaintedAllyMenu(u32 fighterType, BattleFighter *pFighter)
{
    StopTargetFlash();
    PlaySoundById(1);
    pFighter->bSelectedActionIndex = g_pFightState->bMenuCursor;
    g_pFightState->bMenuScreen = BattleMenuNone;
}

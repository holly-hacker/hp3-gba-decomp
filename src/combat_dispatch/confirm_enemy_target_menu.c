#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "combat_gauge.h"
#include "sound.h"

// Targets the enemy slot on the cursor and closes the menu.
void ConfirmEnemyTargetMenu(u32 fighterType, BattleFighter *pFighter)
{
    PlaySoundById(1);
    StopTargetFlash();
    DestroySlotSpGauge(g_pFightState->bMenuCursor, 0);
    pFighter->bSelectedActionIndex = g_pFightState->bMenuCursor;
    g_pFightState->bMenuScreen = BattleMenuNone;
    ZoomBattleCameraOut();
}

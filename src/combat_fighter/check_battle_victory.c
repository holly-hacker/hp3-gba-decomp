#include "types.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"
#include "sound.h"
#include "combat.h"

// Ends the battle in victory once every Enemy fighter is at 0 HP: pushes
// BattleStateVictory and shows the victory message. The caller passes the
// attacking fighter's Actor, which is unused.
void CheckBattleVictory(Actor *actor)
{
    u32 i;

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        if (g_pFightState->pFighters[i].bFighterType == Enemy && g_pFightState->pFighters[i].stats.wHp != 0)
            return;
    }

    PushBattleState(BattleStateVictory);
    g_pFightState->dwBattleResultPending = 1;
    ShowBattleMessage(Victory, 0, 0);
    PlayMusicModule(0x1D);
}

#include "types.h"
#include "battle/battle.h"
#include "graphics/audio.h"

// Ends the battle in victory once every Enemy fighter is at 0 HP: pushes
// battle state 7 and shows the victory message. The caller passes the
// attacking fighter's Object, which is unused.
void CheckBattleVictory(Object *obj)
{
    u32 i;

    for (i = 0; i < g_pFightState->bFighterCount; i++) {
        if (g_pFightState->pFighters[i].bFighterType == Enemy && g_pFightState->pFighters[i].wHp != 0)
            return;
    }

    PushBattleState(7);
    g_pFightState->dwBattleResultPending = 1;
    ShowBattleMessage(Victory, 0, 0);
    PlayMusicModule(0x1D);
}

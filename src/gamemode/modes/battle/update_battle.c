#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"

// Battle mode's pUpdateFn (per-frame tick). See docs/memory-map/battle.md.
void UpdateBattle(void)
{
    u8 timer;
    u32 i;

    sub_0802D3BC();

    if (g_PrevGameModeCtx.dwCurrentGameMode != FolioUniversitas && g_PrevGameModeCtx.dwCurrentGameMode != HelpTopicScreen)
    {
        timer = g_pFightState->bScreenShakeTimer_candidate;
        if (timer != 0)
        {
            g_pFightState->bScreenShakeTimer_candidate = timer - 1;
            sub_0802D640((u8)(g_abBgPriority[4] + 3));
            g_aBgScrollState[0x25] += 0x80000;

            if (g_pFightState->bScreenShakeTimer_candidate != 0)
                return;

            for (i = 0; i < g_pFightState->bFighterCount; i++)
                sub_080039E8(g_pFightState->pFighters[i].pObject);
            return;
        }
    }

    TickBattleTurnStateMachine();
}

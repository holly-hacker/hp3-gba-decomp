#include "types.h"
#include "background.h"
#include "combat_core.h"
#include "combat.h"
#include "modes.h"
#include "mode7.h"

// Battle mode's pUpdateFn (per-frame tick).
void UpdateBattle(void)
{
    u8 timer;
    u32 i;

    UpdateFloorAffineTable();

    if (g_PrevGameModeStackContext.dwCurrentGameMode != FolioUniversitas && g_PrevGameModeStackContext.dwCurrentGameMode != HelpTopicScreen)
    {
        timer = g_pFightState->bIntroSweepTimer;
        if (timer != 0)
        {
            g_pFightState->bIntroSweepTimer = timer - 1;
            SetFloorHeading((u8)(g_FloorEffect.bHeading + 3));
            g_BgState.aLayers[1].scroll.x += 0x80000;

            if (g_pFightState->bIntroSweepTimer != 0)
                return;

            for (i = 0; i < g_pFightState->bFighterCount; i++)
                ClearActorOrbit(g_pFightState->pFighters[i].pActor);
            return;
        }
    }

    TickBattleTurnStateMachine();
}

#include "types.h"
#include "background.h"
#include "mode7.h"
#include "combat_dispatch.h"
#include "color.h"
#include "combat.h"
#include "interrupts.h"
#include "modes.h"
#include "mem.h"
#include "actor.h"
#include "particles.h"
#include "vram.h"
#include "map.h"
#include "screen_transitions.h"

// Battle mode's pDestroyFn. See docs/memory-map/battle.md.
void ExitBattle(void)
{
    GameMode pendingMode;
    u32 slot;

    pendingMode = g_dwPendingGameMode.dwCurrentGameMode & ~0x80;
    g_dwBattleRewardFlagsSnapshot = g_pFightState->bBonusRewardFlags;

    if (pendingMode != FolioUniversitas && pendingMode != FolioBruti &&
        pendingMode != HelpTopicScreen && pendingMode != Help)
    {
        // Battle ended instead of exiting a menu
        u32 partyIndex;

        UnreserveObjPaletteSlot(0);
        FreeAllParticleEmitters();
        FreeAllParticles();
        FreeAllActors(&g_ActiveActorListState.pHead);
        ResetPaletteAnimations();
        ReleaseParticleGfx(0, 0);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        RestoreDefaultVBlankCallback();
        FreeFloorEffect();
        ResetBgLayers();
        ClearPaletteRam();
        sub_0804542C();

        for (slot = 0; slot < ARRAY_COUNT(g_apFighterActors_candidate); slot++)
            g_apFighterActors_candidate[slot] = NULL;
        g_pBattleMessageIconActor_candidate = NULL;

        FreeBlock(g_pFightState->pFighters);
        FreeBlock(g_pFightState->pStagingFighters);
        FreeBlock(g_pFightState->pPendingFighters_candidate);
        FreeBlock(g_pFightState);
        g_pFightState = NULL;

        g_dwPendingGameMode.dwCurrentGameModeArg3 = 0;
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF)
        {
            g_dwPendingGameMode.dwCurrentGameModeArg3 = g_GameModeStackContext.dwCurrentGameModeArg3;
        }
        else if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFE)
        {
            ClearRoomActorStateBuffer();
            g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
            g_GameModeStackContext.dwCurrentGameModeArg1 = 2;
            g_GameModeStackContext.dwCurrentGameMode = FolioUniversitas;
            ClearPaletteRam();
        }

        // Revive party members at 1HP after battle
        for (partyIndex = 0; partyIndex < 4; partyIndex++)
        {
            if (g_aPartyMasterStats[partyIndex].stats.wHp == 0)
                g_aPartyMasterStats[partyIndex].stats.wHp = 1;
        }
    }
    else
    {
        // Suspending for a Folio/Help submode: snapshot every live
        // then pending fighter's Actor (densely packed) instead of tearing
        // the battle down, so it can be restored by InitializeBattle's resume
        // path on return. `fighterIndex` keeps counting across both loops as
        // the destination slot index.
        u32 fighterIndex;
        u32 pendingIndex;

        for (fighterIndex = 0; fighterIndex < g_pFightState->bFighterCount; fighterIndex++)
        {
            if (g_pFightState->pFighters[fighterIndex].pActor->oam.affineMode)
                ReleaseActorAffineSlot(g_pFightState->pFighters[fighterIndex].pActor);

            g_pFightState->pFighters[fighterIndex].pActor->wVramTileAllocId = 0xFFFF;

            memcpy((u8 *)g_pFightState + fighterIndex * sizeof(Actor) + OFFSETOF(FightState, aSuspendedFighterActors_candidate),
                   g_pFightState->pFighters[fighterIndex].pActor, sizeof(Actor));
        }

        for (pendingIndex = 0;
             pendingIndex < g_pFightState->bPendingFighterCount_candidate;
             pendingIndex++, fighterIndex++)
        {
            if (g_pFightState->pPendingFighters_candidate[pendingIndex].pActor->oam.affineMode)
                ReleaseActorAffineSlot(g_pFightState->pPendingFighters_candidate[pendingIndex].pActor);

            g_pFightState->pPendingFighters_candidate[pendingIndex].pActor->wVramTileAllocId = 0xFFFF;

            memcpy((u8 *)g_pFightState + fighterIndex * sizeof(Actor) + OFFSETOF(FightState, aSuspendedFighterActors_candidate),
                   g_pFightState->pPendingFighters_candidate[pendingIndex].pActor, sizeof(Actor));
        }

        if (g_pFightState->bMenuScreen != 0)
            for (fighterIndex = 0; fighterIndex < 7; fighterIndex++)
                ClearFighterActorFlag_candidate(fighterIndex);

        UnreserveObjPaletteSlot(0);
        FreeAllParticleEmitters();
        FreeAllParticles();
        FreeAllActors(&g_ActiveActorListState.pHead);
        ResetPaletteAnimations();
        ReleaseParticleGfx(0, 0);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        RestoreDefaultVBlankCallback();
        FreeFloorEffect();
        ResetBgLayers();
        ClearPaletteRam();
        sub_0804542C();

        for (slot = 0; slot < ARRAY_COUNT(g_apFighterActors_candidate); slot++)
            g_apFighterActors_candidate[slot] = NULL;
        g_pBattleMessageIconActor_candidate = NULL;
    }
}

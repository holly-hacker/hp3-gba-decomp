#include "types.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "mem.h"
#include "graphics.h"

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

        sub_08030960(0);
        sub_080316D4();
        sub_0803171C();
        FreeAllObjects(&g_ActiveObjectListState.pHead);
        sub_0800D2DC();
        sub_08031668(0, 0);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        sub_08026254();
        sub_0802D6B8();
        sub_08007A90();
        ClearPaletteRam();
        sub_0804542C();

        for (slot = 0; slot <= 6; slot++)
            g_apFighterObjects_candidate[slot] = NULL;
        g_pBattleMessageIconObject_candidate = NULL;

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
            ClearRoomObjectStateBuffer();
            g_dwPendingGameMode.dwCurrentGameModeArg1 = 0;
            g_GameModeStackContext.dwCurrentGameModeArg1 = 2;
            g_GameModeStackContext.dwCurrentGameMode = FolioUniversitas;
            ClearPaletteRam();
        }

        // Revive party members at 1HP after battle
        for (partyIndex = 0; partyIndex < 4; partyIndex++)
        {
            if (g_aPartyMasterStats[partyIndex].wHp == 0)
                g_aPartyMasterStats[partyIndex].wHp = 1;
        }
    }
    else
    {
        // Suspending for a Folio Universitas/Help submode: snapshot every live
        // then pending fighter's Object (densely packed) instead of tearing
        // the battle down, so it can be restored by InitializeBattle's resume
        // path on return. `fighterIndex` keeps counting across both loops as
        // the destination slot index.
        u32 fighterIndex;
        u32 pendingIndex;

        for (fighterIndex = 0; fighterIndex < g_pFightState->bFighterCount; fighterIndex++)
        {
            if ((u32)g_pFightState->pFighters[fighterIndex].pObject->bFlags_0xD1 << 30)
                ReleaseObjectAffineSlot(g_pFightState->pFighters[fighterIndex].pObject);

            g_pFightState->pFighters[fighterIndex].pObject->wVramTileAllocId = 0xFFFF;

            memcpy((u8 *)g_pFightState + fighterIndex * sizeof(Object) + OFFSETOF(FightState, aSuspendedFighterObjects_candidate),
                   g_pFightState->pFighters[fighterIndex].pObject, sizeof(Object));
        }

        for (pendingIndex = 0;
             pendingIndex < g_pFightState->bPendingFighterCount_candidate;
             pendingIndex++, fighterIndex++)
        {
            if ((u32)g_pFightState->pPendingFighters_candidate[pendingIndex].pObject->bFlags_0xD1 << 30)
                ReleaseObjectAffineSlot(g_pFightState->pPendingFighters_candidate[pendingIndex].pObject);

            g_pFightState->pPendingFighters_candidate[pendingIndex].pObject->wVramTileAllocId = 0xFFFF;

            memcpy((u8 *)g_pFightState + fighterIndex * sizeof(Object) + OFFSETOF(FightState, aSuspendedFighterObjects_candidate),
                   g_pFightState->pPendingFighters_candidate[pendingIndex].pObject, sizeof(Object));
        }

        if (g_pFightState->bMenuScreen != 0)
            for (fighterIndex = 0; fighterIndex < 7; fighterIndex++)
                ClearFighterObjectFlag_candidate(fighterIndex);

        sub_08030960(0);
        sub_080316D4();
        sub_0803171C();
        FreeAllObjects(&g_ActiveObjectListState.pHead);
        sub_0800D2DC();
        sub_08031668(0, 0);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        sub_08026254();
        sub_0802D6B8();
        sub_08007A90();
        ClearPaletteRam();
        sub_0804542C();

        for (slot = 0; slot <= 6; slot++)
            g_apFighterObjects_candidate[slot] = NULL;
        g_pBattleMessageIconObject_candidate = NULL;
    }
}

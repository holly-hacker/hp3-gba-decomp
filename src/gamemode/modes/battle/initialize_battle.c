#include "types.h"
#include "audio.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "rewards.h"
#include "mem.h"
#include "room.h"

// Battle mode's pInitFn. See docs/memory-map/battle.md.
void InitializeBattle(void)
{
    s32 i;
    u8 *uVar7;
    s32 slot;
    Object *pIconObj;
    u8 flagsBeforeSet;
    s32 flagsBeforeClear;
    s32 clearMask;

    ClearResourceCacheSlots();
    g_BattleMessageIconState_candidate.bIndex = 0xFF;
    g_BattleMessageIconState_candidate.dwParam = 0;
    g_dwBattleRewardFlagsSnapshot = 0;

    // Allocate all 6 fighter objects (3 on the player side, 3 on the enemy side)
    for (i = 0, slot = 0x90; i <= 6; i++)
    {
        g_apFighterObjects_candidate[i] = AllocObjectOfType(i + BattleObjectType_FighterSlot0);
        SetObjectPosition(g_apFighterObjects_candidate[i], i * 0x16 + 0x60, 0x8A);
        g_apFighterObjects_candidate[i]->dwFlags = 0x20000008;
        g_apFighterObjects_candidate[i]->bDepthSortBias = 0x80;
        g_apFighterObjects_candidate[i]->bGfxSlotAndFlags =
            (g_apFighterObjects_candidate[i]->bGfxSlotAndFlags & 0xF) | slot;
        slot += 0x10;
    }

    g_pBattleMessageIconObject_candidate = AllocObjectOfType(i + BattleObjectType_FighterSlot0);
    g_bSelectedFighterSlot_candidate = 0;
    SetObjectPosition(g_pBattleMessageIconObject_candidate, i * 0x16 + 0x60, 0x8A);
    pIconObj = g_pBattleMessageIconObject_candidate;
    pIconObj->dwFlags = 0x20000008;
    // Via a u8 *, not the struct field -- avoids a dead bit-field-store insn
    // that ties this constant's live range with dwFlags' in agbcc's register
    // allocator (see match-function skill, bucket 9).
    *(u8 *)&pIconObj->bDepthSortBias = 0x80;

    flagsBeforeSet = g_pBattleMessageIconObject_candidate->bFlags_0xD1;
    g_pBattleMessageIconObject_candidate->bFlags_0xD1 = flagsBeforeSet | 0x20;

    // The reload must come before clearMask is materialized -- picks the same
    // register pairing the ROM uses.
    flagsBeforeClear = g_pBattleMessageIconObject_candidate->bFlags_0xD1;
    clearMask = ~0xC;
    clearMask &= flagsBeforeClear;
    g_pBattleMessageIconObject_candidate->bFlags_0xD1 = clearMask;

    SetObjectPosition(g_pBattleMessageIconObject_candidate, 2, 0x75);

    for (i = 0; i < 4; i++)
        g_anFaintedRosterIndices[i] = -1;

    if (g_PrevGameModeStackContext.dwCurrentGameMode != FolioUniversitas && g_PrevGameModeStackContext.dwCurrentGameMode != HelpTopicScreen)
    {
        // entered new battle
        g_nBattleXpReward = 0;
        g_nBattleGoldReward = 0;
        g_pFightState = AllocZeroed(0x14C8);
        g_pFightState->pFighters = AllocZeroed(0x1F8);
        g_pFightState->pStagingFighters = AllocZeroed(0x1F8);
        g_pFightState->pPendingFighters_candidate = AllocZeroed(0xD8);

        // set turn order multiplier, see BuildTurnOrder
        if (g_aPartyMasterStats[0].bLevel < 1)
            g_pFightState->bEnemyScalePercent_candidate = 0x40;
        else if (g_aPartyMasterStats[0].bLevel < 2)
            g_pFightState->bEnemyScalePercent_candidate = 0x30;
        else
            g_pFightState->bEnemyScalePercent_candidate = 0x20;

        g_pFightState->bUnk106E = 0;
        InitBattleBackground_candidate();
        SetupBattleRoster();
        uVar7 = GetBattleBackgroundData_candidate();
        LoadEmbeddedPalette_candidate(uVar7, 0, 0x10);
        ResumeBattleAfterSubmode_candidate();
    }
    else
    {
        // entered battle mode by exiting Folio Universitas or the Help screen, ie. this is not a new battle
        InitBattleBackground_candidate();
        RestoreFighterObjects_candidate();
        uVar7 = GetBattleBackgroundData_candidate();
        LoadEmbeddedPalette_candidate(uVar7, 0, 0x10);
        ResumeBattleAfterSubmode_candidate();
    }

    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF)
        PlayMusicModule(g_abBattleMusicByOverworldSlot[g_GameModeStackContext.dwCurrentGameModeArg1]);
    else
        PlayMusicModule(g_abBattleMusicByRoom[g_bCurrentRoomId]);

    g_pFightState->bPendingStatusMessageVariant_candidate = 0x12;
}

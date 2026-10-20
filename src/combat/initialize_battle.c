#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_core.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "sound.h"
#include "modes.h"
#include "mem.h"
#include "map.h"

// Battle mode's pInitFn. See docs/memory-map/battle.md.
void InitializeBattle(void)
{
    s32 i;
    const u8 *uVar7;
    Actor *pIconActor;

    ClearObjPaletteSlots();
    g_StatsPortraitPaletteLoad.bBank = 0xFF;
    g_StatsPortraitPaletteLoad.pPalette = NULL;
    g_dwBattleRewardFlagsSnapshot = 0;

    // Allocate all 6 fighter actors (3 on the player side, 3 on the enemy side)
    for (i = 0; i < ARRAY_COUNT(g_apBattleMenuIconActors); i++)
    {
        g_apBattleMenuIconActors[i] = AllocActorOfType(i + BattleActorType_FighterSlot0);
        SetActorPosition(g_apBattleMenuIconActors[i], i * 0x16 + 0x60, 0x8A);
        g_apBattleMenuIconActors[i]->dwFlags = 0x20000008;
        g_apBattleMenuIconActors[i]->bDepthSortBias = 0x80;
        g_apBattleMenuIconActors[i]->oam.paletteNum = i + 9;
    }

    g_pStatsPortraitActor = AllocActorOfType(i + BattleActorType_FighterSlot0);
    g_dwSelectedBattleMenuIcon = 0;
    SetActorPosition(g_pStatsPortraitActor, i * 0x16 + 0x60, 0x8A);
    pIconActor = g_pStatsPortraitActor;
    pIconActor->dwFlags = 0x20000008;
    pIconActor->bDepthSortBias = 0x80;

    g_pStatsPortraitActor->oam.bpp8 = 1;
    g_pStatsPortraitActor->oam.objMode = 0;

    SetActorPosition(g_pStatsPortraitActor, 2, 0x75);

    for (i = 0; i < ARRAY_COUNT(g_anFaintedRosterIndices); i++)
        g_anFaintedRosterIndices[i] = -1;

    if (g_PrevGameModeStackContext.dwCurrentGameMode != FolioUniversitas && g_PrevGameModeStackContext.dwCurrentGameMode != HelpTopicScreen)
    {
        // entered new battle
        g_nBattleXpReward = 0;
        g_nBattleGoldReward = 0;
        g_pFightState = AllocZeroed(0x14C8);
        g_pFightState->pFighters = AllocZeroed(0x1F8);
        g_pFightState->pStagingFighters = AllocZeroed(0x1F8);
        g_pFightState->pFaintedAllies = AllocZeroed(0xD8);

        // set turn order multiplier, see BuildTurnOrder
        if (g_aPartyMasterStats[0].stats.bLevel < 1)
            g_pFightState->bEnemyScalePercent_candidate = 0x40;
        else if (g_aPartyMasterStats[0].stats.bLevel < 2)
            g_pFightState->bEnemyScalePercent_candidate = 0x30;
        else
            g_pFightState->bEnemyScalePercent_candidate = 0x20;

        g_pFightState->bUnk106E = 0;
        InitBattleDisplay();
        SetupBattleRoster();
        uVar7 = GetBattleFloorGraphic();
        LoadEmbeddedPalette(uVar7, 0, 0x10);
        ResumeBattleAfterSubmode_candidate();
    }
    else
    {
        // Resume after Folio Universitas, Help, or Folio Bruti (whose exit
        // rewrites the previous mode to Folio Universitas).
        InitBattleDisplay();
        RestoreFighterActors_candidate();
        uVar7 = GetBattleFloorGraphic();
        LoadEmbeddedPalette(uVar7, 0, 0x10);
        ResumeBattleAfterSubmode_candidate();
    }

    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF)
        PlayMusicModule(g_abBattleMusicByScriptedEncounter[g_GameModeStackContext.dwCurrentGameModeArg1]);
    else
        PlayMusicModule(g_abBattleMusicByRoom[g_bCurrentRoomId]);

    g_pFightState->bPendingStatusMessageVariant_candidate = 0x12;
}

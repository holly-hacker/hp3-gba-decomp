#include "types.h"
#include "battle.h"
#include "encounters.h"
#include "game_modes.h"

// The random-encounter cell for the current mode-stack args: id/kind/variant
// select the table row, `slot` picks one of its 4 enemy slots.
#define RANDOM_ENCOUNTER_CELL(slot) \
    g_aRandomEncounters[g_GameModeStackContext.dwCurrentGameModeArg1] \
        .aKinds[g_GameModeStackContext.dwCurrentGameModeArg3] \
        .aVariants[g_GameModeStackContext.dwCurrentGameModeArg2][slot]

// The scripted-encounter cell for the current fight id; `slot` picks one of
// its 4 enemy slots.
#define SCRIPTED_ENCOUNTER_CELL(slot) \
    g_aScriptedEncounters[g_GameModeStackContext.dwCurrentGameModeArg1][slot]

// Builds the battle roster: party formation (Buckbeak/Harry/Hermione trio
// for fight 3, else by party size/presence), enemy slots from the scripted
// or random encounter table, then fighters compacted live-first with
// fainted appended. See docs/memory-map/battle.md and docs/formats/encounters.md.
//
// `idx` is shared across all four loops (enemy-slot fill count, then
// compaction write index) -- splitting it into separate counters changes
// the ROM's register allocation and breaks the match.
void SetupBattleRoster(void)
{
    u32 presence;
    u32 slot;
    u8 idx;
    u8 count;

    presence = GetPartyPresenceMask();
    g_pFightState->bFighterCount = GetPartySize();

    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF && g_GameModeStackContext.dwCurrentGameModeArg1 == 3) {
        InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Buckbeak, 1);
        InitPlayerBattleActor(&g_pFightState->pStagingFighters[1], Harry, 2);
        InitPlayerBattleActor(&g_pFightState->pStagingFighters[2], Hermione, 0);
        g_pFightState->bFighterCount = 3;
    } else {
        u32 bCount;
        bCount = g_pFightState->bFighterCount;

        if (bCount == 1) {
            if ((bCount & presence) != 0)
                InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Harry, 1);
            else if ((presence & 4) != 0)
                InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Hermione, 1);
            else if ((presence & 2) != 0)
                InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Ron, 1);

            g_pFightState->bFighterCount = 1;
        } else if (bCount == 2) {
            if ((presence & 1) != 0) {
                InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Harry, 1);
                if ((presence & 4) != 0)
                    InitPlayerBattleActor(&g_pFightState->pStagingFighters[1], Hermione, 0);
                else
                    InitPlayerBattleActor(&g_pFightState->pStagingFighters[1], Ron, 0);
            } else {
                InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Hermione, 0);
                InitPlayerBattleActor(&g_pFightState->pStagingFighters[1], Ron, 1);
            }

            g_pFightState->bFighterCount = 2;
        } else {
            InitPlayerBattleActor(&g_pFightState->pStagingFighters[0], Ron, 2);
            InitPlayerBattleActor(&g_pFightState->pStagingFighters[1], Harry, 1);
            InitPlayerBattleActor(&g_pFightState->pStagingFighters[2], Hermione, 0);

            g_pFightState->bFighterCount = 3;
        }
    }

    for (slot = 0; slot <= 2; slot = (u8)(slot + 1))
        g_pFightState->aAllySlotTurnOrderIndex[slot] |= 0xFF;

    count = g_pFightState->bFighterCount;

    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF) {
        slot = 0;
        idx = 0;
        for (; slot <= 3; slot = (u8)(slot + 1)) {
            if (SCRIPTED_ENCOUNTER_CELL(slot) <= 0xFE) {
                InitMonsterBattleActor(&g_pFightState->pStagingFighters[count + idx], SCRIPTED_ENCOUNTER_CELL(slot), slot);
                g_pFightState->bFighterCount++;
                idx++;
            }

            g_pFightState->aEnemySlotTurnOrderIndex[slot] = 0xFF;
        }
    } else {
        u8 monsterIndex;
        slot = 0;
        idx = 0;
        for (; slot <= 3; slot = (u8)(slot + 1)) {
            if (RANDOM_ENCOUNTER_CELL(slot) <= 0xFE) {
                monsterIndex = RANDOM_ENCOUNTER_CELL(slot);
                InitMonsterBattleActor(&g_pFightState->pStagingFighters[count + idx], monsterIndex, slot);
                g_pFightState->bFighterCount++;
                idx++;

                if (g_saveStateBlock.abMonsterDocLevel[monsterIndex] == 0)
                    g_saveStateBlock.abMonsterDocLevel[monsterIndex] = 2;
            }

            g_pFightState->aEnemySlotTurnOrderIndex[slot] = 0xFF;
        }
    }

    idx = 0;
    count = g_pFightState->bFighterCount;
    slot = 0;

    if (slot < count) {
        for (; slot < g_pFightState->bFighterCount; slot = (u8)(slot + 1))
            g_pFightState->pFighters[slot] = g_pFightState->pStagingFighters[slot];
    }

    slot = 0;
    if (slot < count) {
        for (; slot < count; slot = (u8)(slot + 1)) {
            if (g_pFightState->pFighters[slot].wHp != 0) {
                BattleFighter *stage = g_pFightState->pStagingFighters;
                BattleFighter *dst = (BattleFighter *)(idx * sizeof(BattleFighter) + (u32)stage);
                memcpy(dst, g_pFightState->pFighters + slot, sizeof(BattleFighter));
                g_pFightState->pStagingFighters[idx].nSelectedTargetIndex = 0;
                idx++;
            } else {
                g_pFightState->bFighterCount--;
            }
        }
    }

    slot = 0;
    if (slot < count) {
        u16 hp;
        for (; slot < count; slot = (u8)(slot + 1)) {
            hp = g_pFightState->pFighters[slot].wHp;
            if (hp == 0) {
                BattleFighter *stage = g_pFightState->pStagingFighters;
                BattleFighter *dst = (BattleFighter *)(idx * sizeof(BattleFighter) + (u32)stage);
                memcpy(dst, g_pFightState->pFighters + slot, sizeof(BattleFighter));
                g_pFightState->pStagingFighters[idx].nSelectedTargetIndex = hp;
                idx++;
            }
        }
    }

    JitterEnemyTurnOrder();
    BuildTurnOrder_candidate();
}

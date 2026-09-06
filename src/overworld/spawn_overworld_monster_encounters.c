#include "types.h"
#include "encounters.h"
#include "mem.h"
#include "mt19937.h"
#include "overworld.h"

// Room load: spawn each kind's level-table count of wandering monsters,
// picking each spawn's random variant up front (see
// docs/formats/encounters.md). The placed-position buffer keeps new
// spawns from overlapping; the touch-record state is reset for the new
// room.
void SpawnOverworldMonsterEncounters(u32 countA, u32 countB, u32 countC, u32 encounterId)
{
    u32 monsterId = 0;
    u8 * const pTouchCount = &g_bTouchedMonsterRecordCount;
    u32 counts[3];
    SpawnPosition pos;
    SpawnPosition *pPositions;
    u32 placedCount, terrainType, kindOffset;
    SpawnPosition *pEntry;
    u32 kind, i;
    u16 variant;

    *pTouchCount = 0;
    g_pTouchedWanderingMonster = NULL;

    memset(g_abTouchedMonsterRecords, 0, sizeof(g_abTouchedMonsterRecords));

    if (countA + countB + countC == 0)
        return;

    *pTouchCount = 0;
    placedCount = 0;

    pPositions = AllocZeroed((countA + countB + countC) * sizeof(SpawnPosition));
    counts[0] = countA;
    counts[1] = countB;
    counts[2] = countC;

    for (kind = 0; kind <= 2; kind++) {
        terrainType = GetEncounterKindTerrainType(kind);

        i = 0;
        if (i < counts[kind]) {
            // hacks to get matching decompile
            kindOffset = kind << 4;
            pEntry = (SpawnPosition *)(placedCount * sizeof *pEntry + (u32)pPositions);

            do {
                // BUG: full room returns without FreeBlock, leaking pPositions.
                if (placedCount > 49)
                    return;

                variant = Mt19937RandMax(3);

                // 48 bytes per encounter id, kindOffset for the kind, 4 per variant.
                // Idiomatic form: &g_aRandomEncounters[encounterId].aKinds[kind].aVariants[variant].
                monsterId = PickMaxDamageMonster((const EncounterSlots *)((const u8 *)&g_aRandomEncounters[encounterId] + kindOffset + (variant << 2)));

                if (FindWanderingMonsterSpawnPosition((u32 *)&pos, terrainType, pPositions, placedCount)) {
                    pEntry->x = pos.x;
                    pEntry->y = pos.y;
                    pEntry++;
                    placedCount++;
                    SpawnWanderingMonsterObject(monsterId, pos.x, pos.y, encounterId, variant, kind);
                }
                i++;
            } while (i < counts[kind]);
        }
    }
    FreeBlock(pPositions);
    return;
}

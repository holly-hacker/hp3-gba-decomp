#include "types.h"
#include "combat_fighter.h"
#include "move.h"
#include "random.h"
#include "scroll.h"
#include "map.h"

void TrySpawnWanderingMonster(u32 encounterId, u32 kind)
{
    u32 terrainType;
    u32 monsterId;
    u16 variant;
    s32 camera[2];
    u32 attempt;
    PixelPoint pos;

    variant = Mt19937RandMax(3);
    monsterId = PickMaxDamageMonster(g_aRandomEncounters[encounterId].aKinds[kind].aVariants[variant]);
    terrainType = GetEncounterKindTerrainType(kind);
    GetCameraPosition(camera);

    for (attempt = 0; attempt < 200; attempt++)
    {
        pos.x = Mt19937RandMax(g_RoomSizePixels.dwWidth);
        pos.y = Mt19937RandMax(g_RoomSizePixels.dwHeight);
        // BUG: meant to accept any offscreen position (x < left || y < top || x >= right ||
        // y >= bottom), but only accepts positions below and right of the screen, so no
        // replacement spawns while the camera is at the room's right or bottom edge.
        if (pos.x >= camera[0] && pos.y >= camera[1] && pos.x >= camera[0] + 240 && pos.y >= camera[1] + 160
            && GetCollisionTypeAtPixel_candidate(pos) == terrainType)
        {
            SpawnWanderingMonsterActor(monsterId, pos.x, pos.y, encounterId, variant, kind);
            return;
        }
    }
}

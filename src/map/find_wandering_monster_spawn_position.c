#include "types.h"
#include "hero.h"
#include "math.h"
#include "move.h"
#include "random.h"
#include "scroll.h"
#include "map.h"

// Picks random room pixels until one is on terrainType, at least 60 pixels
// from the player and from every already placed monster.
s32 FindWanderingMonsterSpawnPosition(SpawnPosition *pOutPos, u32 terrainType, const SpawnPosition *pPlacedPositions, u32 placedCount)
{
    IntPoint player;
    u32 attempt;
    u32 i;

    player.x = (s16)(g_pPlayerActor->pos.x >> 16);
    player.y = (s16)(g_pPlayerActor->pos.y >> 16);

    for (attempt = 0; attempt < 200; attempt++)
    {
        pOutPos->x = Mt19937RandMax(g_RoomSizePixels.dwWidth);
        pOutPos->y = Mt19937RandMax(g_RoomSizePixels.dwHeight);
        if (GetCollisionTypeAtPixel((PixelPoint){ pOutPos->x, pOutPos->y }) == terrainType
            && (u32)ApproximateDistance(player, *pOutPos) >= 60)
        {
            for (i = 0; i < placedCount; i++)
            {
                if ((u32)ApproximateDistance(*pOutPos, pPlacedPositions[i]) < 60)
                    break;
            }
            if (i == placedCount)
                return 1;
        }
    }

    return 0;
}

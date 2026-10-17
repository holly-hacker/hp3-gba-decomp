#include "types.h"
#include "buckbeak_minigame.h"
#include "random.h"

// Spawns ring `index` at `position`. Its three parts orbit the center a third
// of a turn apart and start on a random frame of the ring animation.
u32 SpawnBuckbeakMinigameRing(u32 index, BuckbeakMinigameWorldPos position, u32 param)
{
    BuckbeakMinigameRing *pRing = &g_pBuckbeakMinigame->aRings[index];
    ActorOrbit orbit;
    s32 i;
    u32 angleVel;

    pRing->point.world = position;
    pRing->bSpawnParam = param;
    pRing->bActive = 1;

    for (i = 0; i < 3; i++)
    {
        u16 angle;

        pRing->apParts[i] = SpawnActor((index << 16) + i, 0, 0, (const ObjPalette *)gBuckbeakMinigamePalette003Palette);
        SetActorAnimData(pRing->apParts[i], &g_BuckbeakMinigameRingAsset, g_abBuckbeakMinigameRingAnimData, 0);
        pRing->apParts[i]->dwFlags &= ~(ActorFlagVisible | ActorFlagHasAnimation);
        pRing->apParts[i]->bFighterIndex = Mt19937RandMax(6);
        pRing->apParts[i]->oam.priority = 1;
        SetActorAnimFrame(pRing->apParts[i], pRing->apParts[i]->bFighterIndex);
        pRing->apParts[i]->dwStateTimer = 3;

        angle = (i << 8) / 3;
        orbit.wAngleX = angle << 8;
        orbit.wAngleY = -angle << 8;
        angleVel = 0x100;
        orbit.wAngleVelX = angleVel;
        orbit.wAngleVelY = -angleVel;
        orbit.wRadiusX = 10;
        orbit.wRadiusY = 10;
        CopyOrbitParamsFromTable(pRing->apParts[i], &orbit);
    }

    return index;
}

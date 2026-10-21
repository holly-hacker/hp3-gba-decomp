#include "types.h"
#include "actor.h"
#include "background.h"
#include "tea_leaves_minigame.h"

void SlowDivinationTeaLeaves(void)
{
    DivinationTeaLeaf *pLeaf;
    s16 *pVel;
    s32 i;

    for (i = 0; i < DIVINATION_TEA_LEAF_COUNT; i++)
    {
        pLeaf = &g_DivinationTea.aLeaves[i];

        pVel = &pLeaf->pActor->orbitState.orbit.wAngleVelX;
        if (*pVel > 0)
            *pVel -= pLeaf->wOrbitSpeed / 124;
        else if (*pVel < 0)
            *pVel += pLeaf->wOrbitSpeed / 124;

        pVel = &pLeaf->pActor->orbitState.orbit.wAngleVelY;
        if (*pVel > 0)
            *pVel -= pLeaf->wOrbitSpeed / 124;
        else if (*pVel < 0)
            *pVel += pLeaf->wOrbitSpeed / 124;

        pLeaf->wScaleX++;
        pLeaf->wScaleY++;
    }

    g_DivinationTea.dwSwirlSpeed--;
    SetBgRotation(2, (s16)g_BgState.aLayers[2].wAngle, (s16)g_DivinationTea.dwSwirlSpeed);
}

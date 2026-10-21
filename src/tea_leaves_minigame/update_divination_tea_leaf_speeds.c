#include "types.h"
#include "actor.h"
#include "tea_leaves_minigame.h"

void UpdateDivinationTeaLeafSpeeds(void)
{
    s32 i;

    for (i = 0; i < DIVINATION_TEA_LEAF_COUNT; i++)
    {
        if ((s32)g_DivinationTea.dwSwirlSpeed >= g_DivinationTea.aLeaves[i].wOrbitSpeed)
            g_DivinationTea.aLeaves[i].wOrbitSpeed += 0x80;
        else
            g_DivinationTea.aLeaves[i].wOrbitSpeed -= 0x80;

        g_DivinationTea.aLeaves[i].pActor->orbitState.orbit.wAngleVelX = g_DivinationTea.aLeaves[i].wOrbitSpeed;
        g_DivinationTea.aLeaves[i].pActor->orbitState.orbit.wAngleVelY = g_DivinationTea.aLeaves[i].wOrbitSpeed;
    }
}

#include "types.h"
#include "background.h"
#include "tea_leaves_minigame.h"

void SetDivinationTeaSwirlSpeed(u32 speed)
{
    g_DivinationTea.dwSwirlSpeed = speed;
    if (speed > 0xFFF)
        g_DivinationTea.dwSwirlSpeed = 0xFFF;
    if (g_DivinationTea.dwSwirlSpeed < 0x40)
        g_DivinationTea.dwSwirlSpeed = 0x40;

    SetBgRotation(2, (s16)g_BgState.aLayers[2].wAngle, (s16)g_DivinationTea.dwSwirlSpeed);
    UpdateDivinationTeaLeafSpeeds();
}

#include "types.h"
#include "camera.h"
#include "sound.h"
#include "map.h"

void StartEndlessCameraShake(void)
{
    g_aCameraEffects[0].nStep = 0x10000;
    g_aCameraEffects[0].dwFramesLeft = 0;
    g_aCameraEffects[0].bState = 3;
    g_aCameraEffects[0].wCounter = 0;
    g_aCameraEffects[0].dwRunForever = 1;
    PlaySoundById(0x3F);
}

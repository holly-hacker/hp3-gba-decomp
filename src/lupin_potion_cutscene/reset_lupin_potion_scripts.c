#include "lupin_potion_cutscene.h"

void ResetLupinPotionScripts(void)
{
    s32 i;

    for (i = 0; i < LUPIN_POTION_CAST_COUNT; i++)
    {
        g_LupinPotionCutscene.aCastScripts[i].wTimer = 1;
        g_LupinPotionCutscene.aCastScripts[i].wIndex = 0xFFFF;
        g_LupinPotionCutscene.aCastScripts[i].bActive = 1;
        g_LupinPotionCutscene.aCastScripts[i].dwOp = 0;
        g_LupinPotionCutscene.aCastScripts[i].nArg = 0;
    }
    g_LupinPotionCutscene.cameraScript.wTimer = 1;
    g_LupinPotionCutscene.cameraScript.wIndex = 0xFFFF;
    g_LupinPotionCutscene.cameraScript.bActive = 1;
    g_LupinPotionCutscene.cameraScript.dwOp = LupinPotionOpPanX;
    g_LupinPotionCutscene.cameraScript.nArg = 0;
}

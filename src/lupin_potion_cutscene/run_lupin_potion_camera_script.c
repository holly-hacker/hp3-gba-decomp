#include "lupin_potion_cutscene.h"
#include "camera.h"
#include "modes.h"


const LupinPotionScriptCommand g_aLupinPotionCameraScript[LUPIN_POTION_SCRIPT_LENGTH] = {
    { LupinPotionOpPanX, -0x18000, 0, 270 },
    { LupinPotionOpStop, 0, 0, 300 },
    { LupinPotionOpPanY, 0x40000, 0, 310 },
    { LupinPotionOpStop, 0, 0, 490 },
    { LupinPotionOpSetParallax, 0, 0, 500 },
    { LupinPotionOpPanX, 0x18000, 0, 540 },
    { LupinPotionOpStop, 0, 0, 740 },
    { LupinPotionOpEnd, 0, 0, 741 },
};

// The pan speed (g_GameModeStackContext.dwCurrentGameModeArg3) eases to a stop by
// 0x1999 per frame.
void RunLupinPotionCameraScript(void)
{
    const LupinPotionScriptCommand *pCommand;
    FixedPoint delta;

    if (g_LupinPotionCutscene.cameraScript.bActive != 0 && g_LupinPotionCutscene.cameraScript.wTimer != 0
        && --g_LupinPotionCutscene.cameraScript.wTimer == 0)
    {
        g_LupinPotionCutscene.cameraScript.wIndex++;
        pCommand = &g_aLupinPotionCameraScript[g_LupinPotionCutscene.cameraScript.wIndex];
        g_LupinPotionCutscene.cameraScript.wTimer =
            pCommand->wEndFrame - g_GameModeStackContext.dwCurrentGameModeArg2;
        g_LupinPotionCutscene.cameraScript.dwOp = pCommand->dwOp;
        g_LupinPotionCutscene.cameraScript.nArg = pCommand->nArg0;
        if (pCommand->wEndFrame < g_GameModeStackContext.dwCurrentGameModeArg2)
        {
            g_LupinPotionCutscene.cameraScript.wTimer = 0;
            g_LupinPotionCutscene.cameraScript.bActive = 0;
            return;
        }
        switch (pCommand->dwOp)
        {
        case LupinPotionOpSetParallax:
            g_LupinPotionCutscene.bParallaxScroll = pCommand->nArg0;
            break;
        case LupinPotionOpEnd:
            g_LupinPotionCutscene.cameraScript.wTimer = 0;
            g_LupinPotionCutscene.cameraScript.bActive = 0;
            g_GameModeStackContext.dwModeState = 4;
            break;
        }
    }

    switch (g_LupinPotionCutscene.cameraScript.dwOp)
    {
    case LupinPotionOpPanX:
        g_GameModeStackContext.dwCurrentGameModeArg3 = g_LupinPotionCutscene.cameraScript.nArg;
        delta.x = g_GameModeStackContext.dwCurrentGameModeArg3;
        delta.y = 0;
        OffsetCameraFocus(delta, 0);
        break;
    case LupinPotionOpPanY:
        g_GameModeStackContext.dwCurrentGameModeArg3 = 0;
        delta.x = 0;
        delta.y = g_LupinPotionCutscene.cameraScript.nArg;
        OffsetCameraFocus(delta, 0);
        break;
    case LupinPotionOpStop:
        if ((s32)g_GameModeStackContext.dwCurrentGameModeArg3 < -0x1999)
        {
            g_GameModeStackContext.dwCurrentGameModeArg3 += 0x1999;
            delta.x = g_GameModeStackContext.dwCurrentGameModeArg3;
            delta.y = 0;
            OffsetCameraFocus(delta, 0);
        }
        else if ((s32)g_GameModeStackContext.dwCurrentGameModeArg3 > 0x1999)
        {
            g_GameModeStackContext.dwCurrentGameModeArg3 -= 0x1999;
            delta.x = g_GameModeStackContext.dwCurrentGameModeArg3;
            delta.y = 0;
            OffsetCameraFocus(delta, 0);
        }
        else
        {
            g_GameModeStackContext.dwCurrentGameModeArg3 = 0;
            g_LupinPotionCutscene.cameraScript.dwOp = 0;
        }
        break;
    }
}

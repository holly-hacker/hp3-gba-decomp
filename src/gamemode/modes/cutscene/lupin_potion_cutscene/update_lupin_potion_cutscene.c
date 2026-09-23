#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "input.h"
#include "lupin_potion_cutscene.h"
#include "overworld.h"
#include "room_script.h"
#include "room.h"

// The panel slides in (state 1), waits for input (2), slides back out (3) and then runs the
// idle state (0); any of A/B/Select/Start in state 0, or Select/Start elsewhere, ends the
// cutscene (state 4) back in the overworld via exit 0xD. The camera delta scrolls the BGs.
void UpdateLupinPotionCutscene(void)
{
    s32 aPreviousCamera[2];
    s32 aCamera[2];
    s32 aDelta[2];
    s32 i;

    sub_0800A3EC(aPreviousCamera, 0);

    switch (g_GameModeStackContext.dwModeState)
    {
    case 3:
        g_LupinPotionCutscene.nPanelOffset += 3;
        if (g_LupinPotionCutscene.nPanelOffset > 0x27 || (g_wKeysPressed & (KeyA | KeyB)) != 0)
        {
            g_GameModeStackContext.dwModeState = 0;
            g_LupinPotionCutscene.nPanelOffset = 0x28;
            sub_08029380();
        }
        for (i = 0; i <= 7; i++)
        {
            if (g_LupinPotionCutscene.apPanelObject[i] != NULL)
                SetObjectPosition(g_LupinPotionCutscene.apPanelObject[i], i << 5,
                                  g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
        if (g_LupinPotionCutscene.pPanelObject8 != NULL)
            SetObjectPosition(g_LupinPotionCutscene.pPanelObject8, 0, g_LupinPotionCutscene.nPanelOffset + 0x9F);
        if ((g_wKeysPressed & (KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwModeState = 4;
            sub_08029380();
        }
        break;
    case 1:
        g_LupinPotionCutscene.nPanelOffset -= 3;
        if (g_LupinPotionCutscene.nPanelOffset <= 0 || (g_wKeysPressed & (KeyA | KeyB)) != 0)
        {
            g_GameModeStackContext.dwModeState = 2;
            g_LupinPotionCutscene.nPanelOffset = 0;
        }
        for (i = 0; i <= 7; i++)
        {
            if (g_LupinPotionCutscene.apPanelObject[i] != NULL)
                SetObjectPosition(g_LupinPotionCutscene.apPanelObject[i], i << 5,
                                  g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
        if (g_LupinPotionCutscene.pPanelObject8 != NULL)
            SetObjectPosition(g_LupinPotionCutscene.pPanelObject8, 0, g_LupinPotionCutscene.nPanelOffset + 0x9F);
        if ((g_wKeysPressed & (KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwModeState = 4;
            sub_08029380();
        }
    case 2:
    default:
        if ((g_wKeysPressed & (KeyA | KeyB)) != 0)
        {
            if (sub_08029260() == 0)
                g_GameModeStackContext.dwModeState = 3;
        }
        if ((g_wKeysPressed & (KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwModeState = 4;
            sub_08029380();
        }
        break;
    case 0:
        g_GameModeStackContext.dwCurrentGameModeArg2++;
        sub_08028FD8();
        sub_08029144();
        if ((g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
            g_GameModeStackContext.dwModeState = 4;
        break;
    case 4:
        g_abRoomScriptExitParams_candidate[0] = 2;
        PushGameMode_2(Overworld, 0, 0xD);
        break;
    }

    sub_0800A3EC(aCamera, 0);
    aDelta[0] = aCamera[0] - aPreviousCamera[0];
    aDelta[1] = aCamera[1] - aPreviousCamera[1];
    sub_08007D14(0, aDelta[0], aDelta[1]);
    if (g_LupinPotionCutscene.bParallaxScroll != 0)
    {
        sub_08007D14(1, aDelta[0] >> 2, aDelta[1]);
        sub_08007D14(2, -aDelta[0] >> 1, aDelta[1]);
        sub_08007D14(3, -aDelta[0] >> 3, aDelta[1]);
    }
    else
    {
        sub_08007D60(1, aDelta[1]);
        sub_08007D60(2, aDelta[1]);
        sub_08007D60(3, aDelta[1]);
    }
    sub_08007F84(2, &g_aLupinPotionBg2Scroll[0], &g_aLupinPotionBg2Scroll[1]);
    aCamera[0] >>= 16;
    aCamera[1] >>= 16;
    sub_0803E628(aCamera);
}

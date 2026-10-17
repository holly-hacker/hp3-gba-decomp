#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "modes.h"
#include "input.h"
#include "lupin_potion_cutscene.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "overworld/room.h"
#include "scroll.h"

// The panel slides in (state 1), waits for input (2), slides back out (3) and then runs the
// idle state (0); any of A/B/Select/Start in state 0, or Select/Start elsewhere, ends the
// cutscene (state 4) back in the overworld via exit 0xD. The camera delta scrolls the BGs.
void UpdateLupinPotionCutscene(void)
{
    FixedPoint previousCamera;
    FixedPoint camera;
    s32 aDelta[2];
    s32 i;

    GetCameraFocusPosition(&previousCamera, 0);

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
        for (i = 0; i < ARRAY_COUNT(g_LupinPotionCutscene.apPanelActor); i++)
        {
            if (g_LupinPotionCutscene.apPanelActor[i] != NULL)
                SetActorPosition(g_LupinPotionCutscene.apPanelActor[i], i << 5,
                                  g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
        if (g_LupinPotionCutscene.pPanelActor8 != NULL)
            SetActorPosition(g_LupinPotionCutscene.pPanelActor8, 0, g_LupinPotionCutscene.nPanelOffset + 0x9F);
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
        for (i = 0; i < ARRAY_COUNT(g_LupinPotionCutscene.apPanelActor); i++)
        {
            if (g_LupinPotionCutscene.apPanelActor[i] != NULL)
                SetActorPosition(g_LupinPotionCutscene.apPanelActor[i], i << 5,
                                  g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
        if (g_LupinPotionCutscene.pPanelActor8 != NULL)
            SetActorPosition(g_LupinPotionCutscene.pPanelActor8, 0, g_LupinPotionCutscene.nPanelOffset + 0x9F);
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

    GetCameraFocusPosition(&camera, 0);
    aDelta[0] = camera.x - previousCamera.x;
    aDelta[1] = camera.y - previousCamera.y;
    SetBgScrollStep(0, aDelta[0], aDelta[1]);
    if (g_LupinPotionCutscene.bParallaxScroll != 0)
    {
        SetBgScrollStep(1, aDelta[0] >> 2, aDelta[1]);
        SetBgScrollStep(2, -aDelta[0] >> 1, aDelta[1]);
        SetBgScrollStep(3, -aDelta[0] >> 3, aDelta[1]);
    }
    else
    {
        SetBgScrollStepY(1, aDelta[1]);
        SetBgScrollStepY(2, aDelta[1]);
        SetBgScrollStepY(3, aDelta[1]);
    }
    GetBgScroll(2, &g_aLupinPotionBg2Scroll[0], &g_aLupinPotionBg2Scroll[1]);
    camera.x >>= 16;
    camera.y >>= 16;
    SetCameraPosition(&camera.x);
}

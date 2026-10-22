#include "types.h"
#include "background.h"
#include "modes.h"
#include "input.h"
#include "lupin_potion_cutscene.h"
#include "scroll.h"
#include "hero.h"
#include "map.h"

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
            CloseLupinPotionDialogPanel();
        }
        for (i = 0; i < LUPIN_POTION_PANEL_PIECES; i++)
        {
            if (g_LupinPotionCutscene.apPanelActor[i] != NULL)
                SetActorPosition(g_LupinPotionCutscene.apPanelActor[i], i << 5,
                                  g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
        if (g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES] != NULL)
            SetActorPosition(g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES], 0,
                             g_LupinPotionCutscene.nPanelOffset + 0x9F);
        if ((g_wKeysPressed & (KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwModeState = 4;
            CloseLupinPotionDialogPanel();
        }
        break;
    case 1:
        g_LupinPotionCutscene.nPanelOffset -= 3;
        if (g_LupinPotionCutscene.nPanelOffset <= 0 || (g_wKeysPressed & (KeyA | KeyB)) != 0)
        {
            g_GameModeStackContext.dwModeState = 2;
            g_LupinPotionCutscene.nPanelOffset = 0;
        }
        for (i = 0; i < LUPIN_POTION_PANEL_PIECES; i++)
        {
            if (g_LupinPotionCutscene.apPanelActor[i] != NULL)
                SetActorPosition(g_LupinPotionCutscene.apPanelActor[i], i << 5,
                                  g_LupinPotionCutscene.nPanelOffset + 0x9F);
        }
        if (g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES] != NULL)
            SetActorPosition(g_LupinPotionCutscene.apPanelActor[LUPIN_POTION_PANEL_PIECES], 0,
                             g_LupinPotionCutscene.nPanelOffset + 0x9F);
        if ((g_wKeysPressed & (KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwModeState = 4;
            CloseLupinPotionDialogPanel();
        }
    case 2:
    default:
        if ((g_wKeysPressed & (KeyA | KeyB)) != 0)
        {
            if (ShowNextLupinPotionDialogLine() == 0)
                g_GameModeStackContext.dwModeState = 3;
        }
        if ((g_wKeysPressed & (KeySelect | KeyStart)) != 0)
        {
            g_GameModeStackContext.dwModeState = 4;
            CloseLupinPotionDialogPanel();
        }
        break;
    case 0:
        g_GameModeStackContext.dwCurrentGameModeArg2++;
        RunLupinPotionCastScripts();
        RunLupinPotionCameraScript();
        if ((g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
            g_GameModeStackContext.dwModeState = 4;
        break;
    case 4:
        g_abRoomScriptExitParams_candidate[0] = 2;
        PushGameMode_2(Overworld, OverworldEntryEnterRoom, RoomHogwartsGroundsLake);
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

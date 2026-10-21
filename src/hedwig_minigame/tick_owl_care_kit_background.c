#include "types.h"
#include "background.h"
#include "modes.h"
#include "random.h"
#include "screen_transitions.h"
#include "hedwig_minigame.h"

// Every 64 ticks draws a new random background frame on the hidden one of BG2
// and BG3, then crossfades to it over the next 32.
void TickOwlCareKitBackground(void)
{
    u32 timer;
    u32 prevFrame;
    u32 frame;
    u32 bg;
    u32 srcX;
    u32 srcY;

    timer = ++g_OwlCareKitScreen.bBgTimer;
    if (timer < 32)
        return;

    if (timer == 32)
    {
        prevFrame = g_OwlCareKitScreen.bBgFrame;
        frame = Mt19937RandRange(0, 3);
        g_OwlCareKitScreen.bBgFrame = frame;
        if ((u8)frame == prevFrame)
            g_OwlCareKitScreen.bBgFrame = (frame + 1) & 3;

        g_OwlCareKitScreen.bBgFrameOnLayer3 = !g_OwlCareKitScreen.bBgFrameOnLayer3;
        bg = 3;
        if (!g_OwlCareKitScreen.bBgFrameOnLayer3)
            bg = 2;
        srcX = g_aOwlCareBgFrames[g_OwlCareKitScreen.bBgFrame].bX;
        srcY = g_aOwlCareBgFrames[g_OwlCareKitScreen.bBgFrame].bY;
        CopyBgTilemapRectByCell(bg, g_BgState.aLayers[3].pTilemap, 0, 0, srcX, srcY, 0, 0, 30, 20);
        g_OwlCareKitScreen.nBlendStep = -g_OwlCareKitScreen.nBlendStep;
    }
    else if (!(g_OwlCareKitScreen.bBgTimer & 1))
    {
        g_GameModeStackContext.dwModeSubState += g_OwlCareKitScreen.nBlendStep;
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState, 16 - g_GameModeStackContext.dwModeSubState);
        if (g_OwlCareKitScreen.bBgTimer >= 64)
            g_OwlCareKitScreen.bBgTimer = 0;
    }
}

#include "types.h"
#include "math.h"
#include "modes.h"
#include "buckbeak_minigame.h"

const s32 g_aBuckbeakMinigameStartTimes[3] = { 0xB00, 0xA00, 0x900 };

// Puts Buckbeak back at the start with a full clock for the chosen difficulty.
void ResetBuckbeakMinigame(void)
{
    g_pBuckbeakMinigame->player.world.dwHeight = 0x8C0000;
    g_pBuckbeakMinigame->player.world.ground.x = 0;
    g_pBuckbeakMinigame->player.world.ground.y = 0;
    g_pBuckbeakMinigame->dwClimbRate = 0;
    g_pBuckbeakMinigame->dwTurnRate = 0;
    g_pBuckbeakMinigame->dwScore = 0;
    g_pBuckbeakMinigame->dwTimeLeft = g_aBuckbeakMinigameStartTimes[g_GameModeStackContext.dwCurrentGameModeArg3];
    g_pBuckbeakMinigame->dwTimeBonus =
        g_aBuckbeakMinigameStartTimes[g_GameModeStackContext.dwCurrentGameModeArg3] / 3;
    g_pBuckbeakMinigame->bWarningDelay = 0;

    g_pBuckbeakMinigame->nHorizonOffset = -20;
    g_pBuckbeakMinigame->dwHeading.dwValue = 0x590000;
    g_pBuckbeakMinigame->dwSpeed = 0x20000;
    g_pBuckbeakMinigame->dwCameraDistance = 0x140000;
    g_pBuckbeakMinigame->dwCameraHeading.dwValue = 0x590000;
    g_pBuckbeakMinigame->camera.x =
        g_pBuckbeakMinigame->player.world.ground.x - FixedMultiply(g_anSineTable[(g_pBuckbeakMinigame->dwHeading.dwValue >> 16) & 0xFF], 0x140000);
    g_pBuckbeakMinigame->camera.y =
        g_pBuckbeakMinigame->player.world.ground.y
        + FixedMultiply(g_anSineTable[(g_pBuckbeakMinigame->dwHeading.parts.wWhole + 0x40) & 0xFF],
                        g_pBuckbeakMinigame->dwCameraDistance);
    g_pBuckbeakMinigame->dwCameraHeight.dwValue = 0x9B0000;
    g_pBuckbeakMinigame->bNextRing = 0;
    g_pBuckbeakMinigame->bDifficulty = g_GameModeStackContext.dwCurrentGameModeArg3;
}

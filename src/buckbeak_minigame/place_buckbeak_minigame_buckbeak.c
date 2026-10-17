#include "buckbeak_minigame.h"

// Draws Buckbeak at his projected height, shifted sideways as he turns.
void PlaceBuckbeakMinigameBuckbeak(void)
{
    if (ProjectBuckbeakMinigamePoint(&g_pBuckbeakMinigame->player))
    {
        g_pBuckbeakMinigame->pBuckbeak->dwFlags |= ActorFlagVisible;
        SnapActorPosition(g_pBuckbeakMinigame->pBuckbeak, 0x780000 - g_pBuckbeakMinigame->dwTurnRate * 8,
                          g_pBuckbeakMinigame->player.screen.xy.y);
    }
    else
        g_pBuckbeakMinigame->pBuckbeak->dwFlags &= ~ActorFlagVisible;
}

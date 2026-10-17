#include "buckbeak_minigame.h"
#include "mem.h"

void ClearBuckbeakMinigameRings(void)
{
    memset(g_pBuckbeakMinigame->aRings, 0, sizeof(g_pBuckbeakMinigame->aRings));
}

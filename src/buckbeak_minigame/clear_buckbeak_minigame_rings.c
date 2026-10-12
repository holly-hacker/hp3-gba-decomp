#include "types.h"
#include "buckbeak_minigame.h"

void ClearBuckbeakMinigameRings(void)
{
    memset(g_pBuckbeakMinigame->aRings, 0, sizeof(g_pBuckbeakMinigame->aRings));
}

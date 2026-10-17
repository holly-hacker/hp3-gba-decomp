#include "buckbeak_minigame.h"

void MoveBuckbeakMinigameMenuCursor(Actor *pCursor)
{
    SetActorMoveTargetWithDuration(pCursor, 0x78, g_pBuckbeakMinigame->dwMenuSelection * 16 + 0x48, 4);
}

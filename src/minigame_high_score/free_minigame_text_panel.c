#include "types.h"
#include "actor.h"
#include "mem.h"
#include "minigame_high_score.h"

void FreeMinigameTextPanel(MinigameTextPanel *pPanel)
{
    s32 i;

    if (pPanel->pLeftCap != NULL)
        FreeActor(pPanel->pLeftCap);
    if (pPanel->pRightCap != NULL)
        FreeActor(pPanel->pRightCap);

    if (pPanel->ppMiddlePieces != NULL)
    {
        for (i = 0; i < pPanel->middleCount; i++)
        {
            if (pPanel->ppMiddlePieces[i] != NULL)
                FreeActor(pPanel->ppMiddlePieces[i]);
        }
        FreeBlock(pPanel->ppMiddlePieces);
    }

    FreeBlock(pPanel);
}

#include "types.h"
#include "actor.h"
#include "mem.h"
#include "minigame_high_score.h"
#include "gen/graphics/overworld.h"

MinigameTextPanel *SpawnMinigameTextPanel(s32 x, s32 y, s32 widthTiles, u8 priority)
{
    MinigameTextPanel *pPanel;
    s32 middleCount;
    s32 i;

    pPanel = AllocBlock(sizeof(MinigameTextPanel));

    pPanel->pLeftCap = SpawnActor(0, x, y, (const ObjPalette *)gMinigameTextPanelCapPalette);
    SetActorSprite(pPanel->pLeftCap, &g_MinigameTextPanelCapAsset);
    pPanel->pLeftCap->oam.priority = priority;

    pPanel->pRightCap = SpawnActor(0, x + widthTiles * 8, y, (const ObjPalette *)gMinigameTextPanelCapPalette);
    SetActorSprite(pPanel->pRightCap, &g_MinigameTextPanelCapAsset);
    pPanel->pRightCap->oam.hFlip = 1;
    pPanel->pRightCap->oam.priority = priority;

    middleCount = widthTiles - 4;
    if (middleCount < 0)
        middleCount = 0;

    if (middleCount != 0)
    {
        pPanel->ppMiddlePieces = AllocBlock(middleCount * sizeof(Actor *));
        for (i = 0; i < middleCount; i++)
        {
            pPanel->ppMiddlePieces[i] = SpawnActor(0, x + 16 + i * 8, y, (const ObjPalette *)gMinigameTextPanelCapPalette);
            SetActorSprite(pPanel->ppMiddlePieces[i], &g_MinigameTextPanelMiddleAsset);
            pPanel->ppMiddlePieces[i]->oam.priority = priority;
        }
    }
    else
    {
        pPanel->ppMiddlePieces = NULL;
    }

    pPanel->middleCount = middleCount;
    return pPanel;
}

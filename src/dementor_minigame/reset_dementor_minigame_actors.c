#include "types.h"
#include "actor.h"
#include "dementor_minigame.h"

// Faces Harry toward the last cast and returns the Dementors to their start positions.
void ResetDementorMinigameActors(void)
{
    s32 i;

    SetActorSprite(g_DementorMinigame.pHarry, &g_DementorMinigameHarrySprite);
    switch (g_DementorMinigame.dwHarryDirection)
    {
    case 3:
        SetActorAnimFrame(g_DementorMinigame.pHarry, 4);
        g_DementorMinigame.pHarry->oam.hFlip = 0;
        break;
    case 1:
        SetActorAnimFrame(g_DementorMinigame.pHarry, 0);
        g_DementorMinigame.pHarry->oam.hFlip = 0;
        break;
    case 0:
        SetActorAnimFrame(g_DementorMinigame.pHarry, 2);
        g_DementorMinigame.pHarry->oam.hFlip = 0;
        break;
    case 2:
        SetActorAnimFrame(g_DementorMinigame.pHarry, 2);
        g_DementorMinigame.pHarry->oam.hFlip = 1;
        break;
    }

    for (i = 0; i < 4; i++)
    {
        SetActorPosition(g_DementorMinigame.apDementors[i], g_aDementorStartPositions[i].x,
                         g_aDementorStartPositions[i].y);

        switch (i)
        {
        case 3:
            SetActorAnimFrame(g_DementorMinigame.apDementors[3], g_aabDementorFlyAnimData[3][0]);
            break;
        case 1:
            SetActorAnimFrame(g_DementorMinigame.apDementors[1], g_aabDementorFlyAnimData[1][0]);
            break;
        case 0:
            SetActorAnimFrame(g_DementorMinigame.apDementors[0], g_aabDementorFlyAnimData[0][0]);
            break;
        case 2:
            SetActorAnimFrame(g_DementorMinigame.apDementors[2], g_aabDementorFlyAnimData[2][0]);
            break;
        }
    }
}

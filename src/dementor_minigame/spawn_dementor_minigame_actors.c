#include "types.h"
#include "actor.h"
#include "dementor_minigame.h"
#include "minigame_high_score.h"
#include "gen/graphics/overworld.h"

void SpawnDementorMinigameActors(void)
{
    s32 i;

    g_DementorMinigame.pScorePanel = SpawnMinigameTextPanel(0, 0, 10, 1);
    g_DementorMinigame.pLivesPanel = SpawnMinigameTextPanel(0xA0, 0x80, 10, 1);
    g_DementorMinigame.pMissesPanel = SpawnMinigameTextPanel(0, 0x80, 12, 1);

    g_DementorMinigame.pHarry = SpawnActor(0, 0x78, 0x78, (const ObjPalette *)gHarryWalkPalette);
    SetActorSprite(g_DementorMinigame.pHarry, &g_DementorMinigameHarrySprite);
    g_DementorMinigame.pHarry->oam.priority = 2;

    for (i = 0; i < 4; i++)
    {
        g_DementorMinigame.adwDementorStates[i] = DementorIdle;
        g_DementorMinigame.apDementors[i] = SpawnActor(i + 1, g_aDementorStartPositions[i].x,
                                                       g_aDementorStartPositions[i].y,
                                                       (const ObjPalette *)gDementorPalette);
        SetActorSprite(g_DementorMinigame.apDementors[i], &g_DementorMinigameDementorSprite);

        switch (i)
        {
        case 3:
            g_DementorMinigame.apDementors[3]->oam.priority = 3;
            g_DementorMinigame.apDementors[3]->oam.hFlip = 0;
            break;
        case 1:
            g_DementorMinigame.apDementors[1]->oam.priority = 1;
            g_DementorMinigame.apDementors[1]->oam.hFlip = 0;
            break;
        case 0:
            g_DementorMinigame.apDementors[0]->oam.priority = 2;
            g_DementorMinigame.apDementors[0]->oam.hFlip = 1;
            break;
        case 2:
            g_DementorMinigame.apDementors[2]->oam.priority = 2;
            g_DementorMinigame.apDementors[2]->oam.hFlip = 0;
            break;
        }
    }

    ResetDementorMinigameActors();
}

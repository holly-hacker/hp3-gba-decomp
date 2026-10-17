#include "types.h"
#include "actor.h"
#include "minigame_menu.h"
#include "boggart_minigame.h"
#include "minigame_difficulty_select.h"

void SpawnBoggartMinigameActors(void)
{
    s32 i;

    g_BoggartMinigame.pScorePanel = SpawnMinigameTextPanel(0, 0, 10, 1);
    g_BoggartMinigame.pLivesPanel = SpawnMinigameTextPanel(0xA0, 0x80, 10, 1);

    for (i = 0; i < 4; i++)
    {
        g_BoggartMinigame.apStudents[i] = SpawnActor(i, g_aBoggartStudentPositions[i].x,
                                                     g_aBoggartStudentPositions[i].y,
                                                     g_apBoggartStudentPalettes[i]);
        SetActorSprite(g_BoggartMinigame.apStudents[i], &g_aBoggartStudentAssets[i]);

        switch (i)
        {
        case 3:
            g_BoggartMinigame.apStudents[3]->oam.priority = 3;
            break;
        case 1:
            g_BoggartMinigame.apStudents[1]->oam.priority = 1;
            break;
        default:
            g_BoggartMinigame.apStudents[i]->oam.priority = 2;
            break;
        }
    }
}

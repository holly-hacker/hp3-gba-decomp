#include "types.h"
#include "actor.h"
#include "graphics/audio.h"
#include "mt19937.h"
#include "dementor_minigame_inline.h"

// A Dementor within 16 pixels of Harry costs a life and retreats; a retreating one
// stops once back at its start position.
void UpdateDementorMinigameDementors(void)
{
    s32 i;
    u32 found;

    for (i = 0; i < 4; i++)
    {
        found = 0;
        if (g_DementorMinigame.adwDementorStates[i] == DementorApproaching)
        {
            switch (i)
            {
            case 0:
                if ((g_DementorMinigame.apDementors[0]->pos.x >> 16) <= 0x88)
                    found = 1;
                break;
            case 1:
                if ((g_DementorMinigame.apDementors[1]->pos.y >> 16) <= 0x88)
                    found = 1;
                break;
            case 2:
                if ((g_DementorMinigame.apDementors[2]->pos.x >> 16) >= 0x68)
                    found = 1;
                break;
            case 3:
                if ((g_DementorMinigame.apDementors[3]->pos.y >> 16) >= 0x68)
                    found = 1;
                break;
            }
        }

        if (found)
        {
            ShowDementorMinigameDamage();
            if (g_DementorMinigame.bLives != 0)
                g_DementorMinigame.bLives--;
            DrawDementorMinigameLives();

            if (g_DementorMinigame.bLives == 0)
            {
                PlaySoundById(0xA1);
            }
            else
            {
                switch (Mt19937RandRange(0, 1))
                {
                case 0:
                    PlaySoundById(0x9F);
                    break;
                case 1:
                    PlaySoundById(0xA0);
                    break;
                }
            }

            g_DementorMinigame.adwDementorStates[i] = DementorRetreating;
            StartDementorMinigameDementorRetreat(i);
        }
    }

    for (i = 0; i < 4; i++)
    {
        found = 0;
        if (g_DementorMinigame.adwDementorStates[i] == DementorRetreating)
        {
            switch (i)
            {
            case 0:
                if ((g_DementorMinigame.apDementors[0]->pos.x >> 16)
                    >= g_aDementorStartPositions[0].x - 4)
                    found = 1;
                break;
            case 1:
                if ((g_DementorMinigame.apDementors[1]->pos.y >> 16)
                    >= g_aDementorStartPositions[1].y - 4)
                    found = 1;
                break;
            case 2:
                if ((g_DementorMinigame.apDementors[2]->pos.x >> 16)
                    <= g_aDementorStartPositions[2].x + 4)
                    found = 1;
                break;
            case 3:
                if ((g_DementorMinigame.apDementors[3]->pos.y >> 16)
                    <= g_aDementorStartPositions[3].y + 4)
                    found = 1;
                break;
            }
        }

        if (found)
        {
            g_DementorMinigame.adwDementorStates[i] = DementorIdle;
            SetActorVelocity(g_DementorMinigame.apDementors[i], 0, 0);
        }
    }
}

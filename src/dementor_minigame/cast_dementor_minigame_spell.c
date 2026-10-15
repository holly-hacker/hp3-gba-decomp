#include "types.h"
#include "actor.h"
#include "graphics/audio.h"
#include "dementor_minigame_inline.h"

void CastDementorMinigameSpell(s32 direction)
{
    g_DementorMinigame.dwHarryDirection = direction;
    SetActorAnimData(g_DementorMinigame.pHarry, &g_DementorMinigameHarryCastSprite,
                     g_aabDementorMinigameHarryCastAnimData[direction], 0);
    g_DementorMinigame.dwSpellTimer = 3;
    g_DementorMinigame.dwSpellDirection = direction;

    if (direction == 2)
        g_DementorMinigame.pHarry->oam.hFlip = 1;
    else
        g_DementorMinigame.pHarry->oam.hFlip = 0;

    if (g_DementorMinigame.adwDementorStates[direction] == DementorApproaching)
    {
        PlaySoundById(0x50);
        RepelDementorMinigameDementor(direction);
    }
    else
    {
        if (++g_DementorMinigame.bMisses == 3)
        {
            g_DementorMinigame.bMisses = 0;
            if (g_DementorMinigame.bLives != 0)
                g_DementorMinigame.bLives--;
            DrawDementorMinigameLives();
        }

        PlaySoundById(0x4B);
        DrawDementorMinigameMisses();
    }
}

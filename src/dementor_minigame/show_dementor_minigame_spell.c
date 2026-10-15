#include "types.h"
#include "actor.h"
#include "dementor_minigame.h"

void ShowDementorMinigameSpell(s32 direction)
{
    SnapActorPosition(g_DementorMinigame.pSpellActor,
                      g_aDementorMinigameSpellPositions[direction].x << 16,
                      g_aDementorMinigameSpellPositions[direction].y << 16);
    SetActorAnimData(g_DementorMinigame.pSpellActor, &g_DementorMinigameSpellSprite,
                     g_aabDementorMinigameSpellAnimData[direction], 0);

    switch (direction)
    {
    case 3:
        g_DementorMinigame.pSpellActor->oam.priority = 3;
        SetActorDepthSortBias(g_DementorMinigame.pSpellActor, 0);
        break;
    case 1:
        g_DementorMinigame.pSpellActor->oam.priority = 1;
        SetActorDepthSortBias(g_DementorMinigame.pSpellActor, 0xFF);
        break;
    case 0:
        g_DementorMinigame.pSpellActor->oam.priority = 2;
        SetActorDepthSortBias(g_DementorMinigame.pSpellActor, 0);
        break;
    case 2:
        g_DementorMinigame.pSpellActor->oam.priority = 2;
        SetActorDepthSortBias(g_DementorMinigame.pSpellActor, 0);
        break;
    }

    g_DementorMinigame.pSpellActor->dwFlags |= ActorFlagVisible;
    g_DementorMinigame.dwSpellHideTimer = 8;
}

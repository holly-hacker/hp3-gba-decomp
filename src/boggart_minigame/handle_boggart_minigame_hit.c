#include "types.h"
#include "actor.h"
#include "modes.h"
#include "boggart_minigame_inline.h"
#include "gen/graphics/minigames/boggart.h"

void HandleBoggartMinigameHit(void)
{
    Actor *pActor;

    if (g_BoggartMinigame.dwBoggartDirection == 0)
    {
        pActor = SpawnActor(4, (s16)(g_BoggartMinigame.pActor->pos.x >> 16),
                            (s16)(g_BoggartMinigame.pActor->pos.y >> 16),
                            (const ObjPalette *)gBoggartRidiculousFormPalette);
        SetActorSprite(pActor, &g_aBoggartFormAssets[4]);
        pActor->oam.priority = 2;
        SetActorAnimFrame(pActor, 0);
        g_BoggartMinigame.pActor->dwFlags |= 0x82;
        g_BoggartMinigame.pActor = pActor;
    }
    else
    {
        SetActorAnimData(g_BoggartMinigame.pActor,
                         &g_aBoggartFormAssets[g_BoggartMinigame.dwBoggartDirection],
                         g_aabBoggartHitAnimData[g_BoggartMinigame.dwBoggartDirection], 0);
    }

    switch (g_BoggartMinigame.dwBoggartDirection)
    {
    case 2:
        SetActorVelocity(g_BoggartMinigame.pActor, GetBoggartMinigameBoggartVelocity(1) * 3, 0);
        break;
    case 3:
        SetActorVelocity(g_BoggartMinigame.pActor, 0, GetBoggartMinigameBoggartVelocity(1) * 3);
        break;
    case 0:
        SetActorVelocity(g_BoggartMinigame.pActor, GetBoggartMinigameBoggartVelocity(0) * 3, 0);
        break;
    case 1:
        SetActorVelocity(g_BoggartMinigame.pActor, 0, GetBoggartMinigameBoggartVelocity(0) * 3);
        break;
    }

    ClearBoggartMinigameMessage();
    DrawBoggartMinigameMessage(0x58F);  // "Great!"

    AddBoggartMinigameScore(GetBoggartMinigameRoundPoints());
    g_BoggartMinigame.dwCountdown = 3;
    g_GameModeStackContext.dwModeState = BoggartMinigameStateNextRound;
}

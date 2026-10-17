#include "types.h"
#include "actor.h"
#include "random.h"
#include "boggart_minigame.h"

void SpawnBoggartMinigameBoggart(void)
{
    s32 direction;

    do
        direction = Mt19937RandRange(0, 3);
    while (direction == g_BoggartMinigame.dwBoggartDirection);

    g_BoggartMinigame.pActor = SpawnActor(direction + 4, 0x78, 0x65, g_apBoggartFormPalettes[direction]);
    SetActorSprite(g_BoggartMinigame.pActor, &g_aBoggartFormAssets[direction]);
    g_BoggartMinigame.pActor->oam.priority = 2;
    g_BoggartMinigame.dwBoggartDirection = direction;
}

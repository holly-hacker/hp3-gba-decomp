#include "types.h"
#include "game/game_modes.h"
#include "boggart_minigame.h"

u32 HasBoggartMinigameBoggartReturnedToCenter(void)
{
    switch (g_BoggartMinigame.dwBoggartDirection)
    {
    case 0:
        if ((s16)(g_BoggartMinigame.pActor->pos.x >> 16) <= 0x78)
            return 1;
        break;
    case 1:
        if ((s16)(g_BoggartMinigame.pActor->pos.y >> 16) <= 0x65)
            return 1;
        break;
    case 2:
        if ((s16)(g_BoggartMinigame.pActor->pos.x >> 16) > 0x77)
            return 1;
        break;
    case 3:
        if ((s16)(g_BoggartMinigame.pActor->pos.y >> 16) > 0x64)
            return 1;
        break;
    }
    return 0;
}

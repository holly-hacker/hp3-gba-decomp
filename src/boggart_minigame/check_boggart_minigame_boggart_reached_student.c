#include "types.h"
#include "actor.h"
#include "boggart_minigame.h"

u32 CheckBoggartMinigameBoggartReachedStudent(void)
{
    u32 reached = 0;

    switch (g_BoggartMinigame.dwBoggartDirection)
    {
    case 0:
        if ((s16)(g_BoggartMinigame.pActor->pos.x >> 16) >= g_aBoggartStudentPositions[0].x - 0x10)
            reached = 1;
        break;
    case 1:
        if ((s16)(g_BoggartMinigame.pActor->pos.y >> 16) >= g_aBoggartStudentPositions[1].y - 0x10)
            reached = 1;
        break;
    case 2:
        if ((s16)(g_BoggartMinigame.pActor->pos.x >> 16) <= g_aBoggartStudentPositions[2].x + 0x10)
            reached = 1;
        break;
    case 3:
        if ((s16)(g_BoggartMinigame.pActor->pos.y >> 16) <= g_aBoggartStudentPositions[3].y + 0x10)
            reached = 1;
        break;
    }

    if (reached)
    {
        HandleBoggartMinigameMiss(1);
        return 1;
    }
    return 0;
}

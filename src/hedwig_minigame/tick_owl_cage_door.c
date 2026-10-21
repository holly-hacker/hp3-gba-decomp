#include "types.h"
#include "actor.h"
#include "hedwig_minigame.h"

// Holds the door open (2) or shut (0) once it finishes opening or closing.
void TickOwlCageDoor(Actor *pDoor)
{
    if (pDoor->dwFlags & ActorFlagActionAnimDone)
    {
        pDoor->dwFlags &= ~ActorFlagActionAnimDone;
        if (pDoor->bActionSubState == 1)
            pDoor->bActionSubState = 2;
        else if (pDoor->bActionSubState == 3)
            pDoor->bActionSubState = 0;
    }
}

#include "buckbeak_minigame.h"

void ReleaseBuckbeakMinigameActor(Actor **ppActor)
{
    if (*ppActor != NULL)
    {
        (*ppActor)->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        *ppActor = NULL;
    }
}

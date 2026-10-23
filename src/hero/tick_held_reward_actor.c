#include "actor.h"
#include "dialog.h"
#include "overworld/overworld.h"

// Holds the item until dwStateTimer runs out and no dialog box is open.
void TickHeldRewardActor(Actor *actor)
{
    if (actor->dwStateTimer != 0)
        actor->dwStateTimer--;
    else if (g_DialogState.dwState != 1)
        actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
}

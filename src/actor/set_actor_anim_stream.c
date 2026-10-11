#include "actor.h"

// Starts the animation command stream at command startCommand of pAnimData,
// keeping the current sprite record. A null pAnimData stops the stream.
void SetActorAnimStream(Actor *actor, const void *pAnimData, u8 startCommand)
{
    actor->anim.pAnimFrameBase = (u8 *)pAnimData;
    actor->anim.pAnimFrameCursor = (u8 *)pAnimData;

    if (pAnimData != 0) {
        actor->anim.pAnimFrameBase += startCommand * 2;
        actor->anim.pAnimFrameCursor += startCommand * 2;
        RunActorAnimCommands(actor);
        LoadActorAnimFrameBounds(actor);
    }
}

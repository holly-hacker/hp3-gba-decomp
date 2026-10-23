#include "actor.h"

// Like SetActorAnimData, but only the cursor starts at command startCommand;
// the stream still loops back to the start of pAnimData.
void SetActorAnimDataAtCommand(Actor *actor, const void *pAnimTable, const void *pAnimData, u8 startCommand)
{
    actor->anim.pAnimFrameBase = (u8 *)pAnimData;
    actor->anim.pAnimFrameCursor = (u8 *)pAnimData + startCommand * 2;

    if (actor->anim.pAnimTable != pAnimTable) {
        actor->anim.pAnimTable = (ActorAssetRecord *)pAnimTable;
        actor->anim.bLoadedAnimFrame = 0xFF;
        actor->anim.bLastAnimFrameValue = 0xFF;
    }

    RunActorAnimCommands(actor);
    LoadActorAnimFrameBounds(actor);
}

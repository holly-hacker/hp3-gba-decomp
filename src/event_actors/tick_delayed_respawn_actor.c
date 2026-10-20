#include "types.h"
#include "actor.h"
#include "area.h"
#include "commands.h"
#include "event_actors.h"
#include "overworld/room_script_bytecode.h"

// Waits dwStateTimer frames, then runs the row/chain. When the room script yielded on the
// delayed-respawn opcode that spawned it, it resumes that script instead, after respawning a
// row that has no chain.
void TickDelayedRespawnActor(Actor *actor)
{
    switch (actor->bActionState)
    {
    case 0:
        if ((s32)actor->dwStateTimer-- == 0)
            SetActorActionState(actor, 1);
        break;
    case 1:
        actor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        if (g_dwRoomScriptRunState == 2
            && (g_bRoomScriptYieldOpcode == RSOP_DelayedRespawnRowAndRunChain
                || g_bRoomScriptYieldOpcode == RSOP_DelayedRespawnRowAndRunChainFrames))
        {
            if (actor->modeState.actor.bDelayedChainRow == 0 && actor->modeState.actor.bDelayedRespawnRow != 0)
                RespawnGroupAndRunChain(actor->modeState.actor.bDelayedRespawnRow,
                                        actor->modeState.actor.bDelayedChainRow);
            ResumeRoomScriptChain();
        }
        else
        {
            RespawnGroupAndRunChain(actor->modeState.actor.bDelayedRespawnRow,
                                    actor->modeState.actor.bDelayedChainRow);
        }
        break;
    }

    actor->bActionFlags = 0;
}

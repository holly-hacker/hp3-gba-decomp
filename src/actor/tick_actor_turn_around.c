#include "actor.h"

// Action state 0x1B: turns the actor around every scriptState.bytes.bTurnInterval
// ticks, after a 15-tick pause.
void TickActorTurnAround(Actor *actor)
{
    switch (actor->bActionSubState) {
    case 0:
        SetActorActionSubState(actor, 3);
        actor->dwStateTimer = actor->scriptState.bytes.bTurnInterval;
        break;
    case 3:
        if (--actor->dwStateTimer == -1) {
            SetActorActionSubState(actor, 6);
            actor->dwStateTimer = 15;
        }
        break;
    case 6:
        if (--actor->dwStateTimer == -1) {
            if (actor->dwFlags & ActorFlagFourWayDirections)
                actor->bFacing = g_abTurnAroundDirection4[actor->bFacing];
            else
                actor->bFacing = g_abTurnAroundDirection[actor->bFacing];
            SetActorActionSubState(actor, 3);
            actor->dwStateTimer = actor->scriptState.bytes.bTurnInterval;
        }
        break;
    }
}

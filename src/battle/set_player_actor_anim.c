#include "types.h"
#include "battle/battle.h"
#include "mt19937.h"

// state 0 (idle) re-rolls one of 2 random idle starting frames.
void SetPlayerActorAnim(Actor *actor, s32 state)
{
    if (actor->dwFlags & ActorFlagVisible)
    {
        actor->dwFlags &= ~(ActorFlagVisible | ActorFlagActionAnimDone);
        if (state == 0)
        {
            SetActorAnimData(actor, (u8 *)&g_aFighterAnimTable[actor->wActorType] + state * 0x10,
                               g_aFighterAnimDataTable[actor->wActorType][state], 0);
            actor->anim.pAnimFrameCursor = actor->anim.pAnimFrameBase + Mt19937RandMax(2) * 4;
            SetActorAnimFrame(actor, *actor->anim.pAnimFrameCursor);
        }
        else
        {
            SetActorAnimData(actor, (u8 *)&g_aFighterAnimTable[actor->wActorType] + state * 0x10,
                               g_aFighterAnimDataTable[actor->wActorType][state], 0);
        }
        actor->dwFlags |= ActorFlagVisible;
    }
    else
    {
        actor->dwFlags &= ~ActorFlagActionAnimDone;
        SetActorAnimData(actor, (u8 *)&g_aFighterAnimTable[actor->wActorType] + state * 0x10,
                           g_aFighterAnimDataTable[actor->wActorType][state], 0);
    }
}

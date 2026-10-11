#include "types.h"
#include "battle/battle.h"
#include "mt19937.h"

// state 0 (idle) re-rolls one of 2 random idle starting frames.
void SetPlayerObjectAnim(Actor *obj, s32 state)
{
    if (obj->dwFlags & ActorFlagVisible)
    {
        obj->dwFlags &= ~(ActorFlagVisible | ActorFlagActionAnimDone);
        if (state == 0)
        {
            SetActorAnimData(obj, (u8 *)&g_aFighterAnimTable[obj->wActorType] + state * 0x10,
                               g_aFighterAnimDataTable[obj->wActorType][state], 0);
            obj->anim.pAnimFrameCursor = obj->anim.pAnimFrameBase + Mt19937RandMax(2) * 4;
            SetActorAnimFrame(obj, *obj->anim.pAnimFrameCursor);
        }
        else
        {
            SetActorAnimData(obj, (u8 *)&g_aFighterAnimTable[obj->wActorType] + state * 0x10,
                               g_aFighterAnimDataTable[obj->wActorType][state], 0);
        }
        obj->dwFlags |= ActorFlagVisible;
    }
    else
    {
        obj->dwFlags &= ~ActorFlagActionAnimDone;
        SetActorAnimData(obj, (u8 *)&g_aFighterAnimTable[obj->wActorType] + state * 0x10,
                           g_aFighterAnimDataTable[obj->wActorType][state], 0);
    }
}
